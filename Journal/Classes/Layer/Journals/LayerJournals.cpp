//
//  LayerJournals.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/5.
//

#include "Journal.h"
#include "Define.h"
#include "NotificationManager.h"
#include "RichViewManager.h"
#include "DataManager.h"
#include "DataJournal.h"
#include "DataUser.h"
#include "JournalsCell.h"
#include "LayerComment.h"
#include "LayerMain.h"
#include "LayerJournalClassify.h"
#include "LayerJournals.h"


#define JOURNAL_CELL_SIZE 3.0 //table显示的cell数量


CLayerJournals::CLayerJournals()
:m_pTableView(nullptr)
,m_fTableViewHeight(0.0f)
,m_showType(ShowType::None)
{
    NotificationManager::getInstance()->registerNotification(NOTIFY_TYPE::journal_data_change, this);
}


CLayerJournals::~CLayerJournals()
{
    NotificationManager::getInstance()->unregisterNotification(NOTIFY_TYPE::journal_data_change, this);
}


bool CLayerJournals::init()
{
    if(!Layer::init()){
        return false;
    }
    
    _initUI();
    
    return true;
}


void CLayerJournals::_initUI()
{
    m_winSize = Director::getInstance()->getWinSize();
    
    auto bg = Sprite::create("journal_top.png");
    bg->setPosition(Vec2(m_winSize.width/2, m_winSize.height - bg->getContentSize().height/2));
    this->addChild(bg);
    
    //头像
    auto avater = Sprite::create("avatar_default.png");
    avater->setPosition(Vec2(bg->getContentSize().width/2, bg->getContentSize().height/2));
    bg->addChild(avater);
    
    //名字
    auto username = CDataManager::getInstance()->getDataUser()->getUserInfo().alias;
    auto labelname = Label::createWithTTF(username, MY_FONT_CHINESE, 35);
    labelname->setPosition(Vec2(bg->getContentSize().width/2, 50));
    labelname->enableBold();
    bg->addChild(labelname);
    
    //width适配
    auto width = m_winSize.width * 0.15f;
    width = bg->convertToNodeSpace(Vec2(width,0)).x;
    
    //写日志
    auto btnAdd = Button::create("btn_add.png");
    btnAdd->setPosition(Vec2(width, bg->getContentSize().height/2 + 100));
    btnAdd->addClickEventListener([](Ref* r){
        CRichViewManager::getInstance()->newJournal();
    });
    bg->addChild(btnAdd);
    
    //TODO: 搜索不做
    auto btnSearch = Button::create("btn_search.png");
    btnSearch->setPosition(Vec2(width, bg->getContentSize().height/2));
    btnSearch->addClickEventListener([](Ref* r){
    });
    bg->addChild(btnSearch);
    
    //弹出板子
    auto btnDrawer = Button::create("btn_drawer.png");
    btnDrawer->setPosition(Vec2(width, bg->getContentSize().height/2 - 100));
    btnDrawer->addClickEventListener([&](Ref* r){
        auto layer = CLayerJournalClassify::create();
        this->addChild(layer);
    });
    bg->addChild(btnDrawer);
    
    
    //TODO: 滚动顶部汉字?细节先不做?
    
    
    
    //tableview
    this->setShowType(ShowType::All);
    m_fTableViewHeight = m_winSize.height - bg->getContentSize().height - MAIN_BOTTOM_HEIGHT;
    m_pTableView = TableView::create(this, Size(m_winSize.width, m_fTableViewHeight));
    m_pTableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
    m_pTableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    m_pTableView->setDelegate(this);
    m_pTableView->setPositionY(MAIN_BOTTOM_HEIGHT);
    this->addChild(m_pTableView);
    m_pTableView->reloadData();
}


void CLayerJournals::setShowType(ShowType type)
{
    if (m_showType == type)
    {
        return;
    }
    
    m_showType = type;
    _updateData();
}

void CLayerJournals::notifyEvent(NOTIFY_TYPE type, void* pVoid)
{
    if (type == NOTIFY_TYPE::journal_data_change)
    {
        _updateData();
    }
}

void CLayerJournals::_updateData()
{
    m_showJournals = CDataManager::getInstance()->getDataJournal()->getJournals();
    if (m_showType == ShowType::Public)
    {
        for (auto it = m_showJournals.begin(); it != m_showJournals.end();)
        {
            if (!it->isPublic)
            {
                it = m_showJournals.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
    else if (m_showType == ShowType::Private)
    {
        for (auto it = m_showJournals.begin(); it != m_showJournals.end();)
        {
            if (it->isPublic)
            {
                it = m_showJournals.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
    
    //排个序
    std::sort(m_showJournals.begin(), m_showJournals.end(), [](const Journal_Info&lhs, const Journal_Info& rhs){
        return lhs.createTime > rhs.createTime;
    });
    
    //刷新tableview
    if (m_pTableView)
    {
        m_pTableView->reloadData();
    }
}

void CLayerJournals::scrollViewDidScroll(cocos2d::extension::ScrollView* view)
{
}

void CLayerJournals::scrollViewDidZoom(cocos2d::extension::ScrollView* view)
{
}

void CLayerJournals::tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)
{
    auto tableCell = dynamic_cast<CJournalsCell*>(cell);
    if (!tableCell)
    {
        return;
    }
    if (CRichViewManager::getInstance()->getRichViewType() != RichViewType::none)
    {
        return;
    }
    int idx = static_cast<int>(cell->getIdx());
    CRichViewManager::getInstance()->showJournal(m_showJournals[idx], true);
}

cocos2d::Size CLayerJournals::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    return Size(m_winSize.width, m_fTableViewHeight/JOURNAL_CELL_SIZE);
}

cocos2d::extension::TableViewCell* CLayerJournals::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    TableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = CJournalsCell::create();
        cell->setContentSize(tableCellSizeForIndex(table,idx));
    }
    dynamic_cast<CJournalsCell*>(cell)->updateCell(m_showJournals, static_cast<int>(idx));
    return cell;
}

ssize_t CLayerJournals::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
    return m_showJournals.size();
}


void CLayerJournals::endWithHttpData(eHttpType myType, HttpResponseInfo rep)
{
    if (myType == eHttpType::comment_list)
    {
        if (rep.status == eHttpStatus::success && this->isVisible())
        {
            if (!Director::getInstance()->getRunningScene()->getChildByName("CLayerComment"))
            {
                auto layerComment = CLayerComment::create();
                layerComment->setCommentType(CommentType::self);
                layerComment->setName("CLayerComment");
                Director::getInstance()->getRunningScene()->addChild(layerComment);//直接加到最上面
            }
        }
    }
}
