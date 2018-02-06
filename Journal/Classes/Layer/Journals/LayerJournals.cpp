//
//  LayerJournals.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/5.
//

#include "Config.h"
#include "RichText.h"
#include "DataManager.h"
#include "DataJournal.h"
#include "DataUser.h"
#include "JournalsCell.h"
#include "LayerMain.h"
#include "LayerJournalClassify.h"
#include "LayerJournals.h"


#define JOURNAL_CELL_SIZE 5 //table显示的cell数量


CLayerJournals::CLayerJournals()
:m_pTableView(nullptr)
,m_fTableViewHeight(0.0f)
,m_showType(ShowType::All)
{
}


CLayerJournals::~CLayerJournals()
{
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
    auto username = CDataManager::getInstance()->getDataUser()->getUserInfo().username;
    auto labelname = Label::createWithTTF(username, MY_FONT_ENGLISH, 35);
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
        CRichText::getInstance()->haha();
    });
    bg->addChild(btnAdd);
    
    //搜索不做
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
    
    
    //滚动顶部汉字????
    
    
    
    //tableview
    this->setShowType(m_showType);
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
    m_showJournals = CDataManager::getInstance()->getDataJournal()->getJournals();
    if (type == ShowType::Public)
    {
        
    }
    else if (type == ShowType::Private)
    {
        
    }
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








