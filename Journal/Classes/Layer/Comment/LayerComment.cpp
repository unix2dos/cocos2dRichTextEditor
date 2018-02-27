//
//  LayerComment.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/26.
//

#include "Journal.h"
#include "Define.h"
#include "CommonUtils.h"
#include "LayerMain.h"
#include "CommentCell.h"
#include "DataManager.h"
#include "DataJournal.h"
#include "LayerComment.h"


#define COMMENT_CELL_SIZE 11 //table显示的cell数量
#define COMMENT_BOTTOM_HEIGHT 100 //评论框高度


CLayerComment::CLayerComment()
:m_pTableView(nullptr)
,m_fTableViewHeight(0.0f)
,m_iJournalId(-1)
{
    
}


CLayerComment::~CLayerComment(){
    
}


bool CLayerComment::init()
{
    if(!Layer::init()){
        return false;
    }
    
    _initUI();
    
    return true;
}


void CLayerComment::_initUI()
{
    m_winSize = Director::getInstance()->getWinSize();
    
    m_fTableViewHeight = m_winSize.height;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    m_fTableViewHeight -= 50;//电池栏
#endif
    
    auto bg = LayerColor::create(Color4B(255, 255, 255, 255));
    this->addChild(bg);
    
    
    auto diffY = 30;
    auto btnBack = Button::create("ui_back.png");
    btnBack->setPosition(Vec2(30, m_fTableViewHeight-diffY));
    this->addChild(btnBack);
    btnBack->addClickEventListener([&](Ref* r){
        this->removeFromParent();
    });
    
    auto label = Label::createWithTTF("COMMENT", MY_FONT_CHINESE, 30);
    label->setPosition(Vec2(m_winSize.width/2, m_fTableViewHeight-diffY));
    label->setTextColor(Color4B(0,0,0,255));
    this->addChild(label);
    m_fTableViewHeight -= diffY*2;//减去伪导航栏
    m_fTableViewHeight -= COMMENT_BOTTOM_HEIGHT;//评论栏
    
    
    
    m_pTableView = TableView::create(this, Size(m_winSize.width, m_fTableViewHeight));
    m_pTableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
    m_pTableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    m_pTableView->setDelegate(this);
    m_pTableView->setPositionY(COMMENT_BOTTOM_HEIGHT);
    this->addChild(m_pTableView);
    m_pTableView->reloadData();
    
    
    //评论框
    {
        auto layerColor = LayerColor::create(Color4B(240, 240, 240, 255), m_winSize.width, COMMENT_BOTTOM_HEIGHT);
        this->addChild(layerColor);
        
        auto node = Node::create();
        auto pBack = Sprite::create("login_input.png");
        node->addChild(pBack);
        
        auto editBoxSize = Size(480, 70);
        ui::EditBox* r = ui::EditBox::create(editBoxSize, ui::Scale9Sprite::create());
        r->setPlaceHolder("add comment");
        r->setPlaceholderFontSize(40);
        r->setPlaceholderFontColor(Color3B::GRAY);
        r->setFontColor(Color3B::BLACK);
        r->setFontSize(40);
        node->addChild(r);
        node->setPosition(Vec2(layerColor->getContentSize().width/2, layerColor->getContentSize().height/2));
        layerColor->addChild(node);
        
        auto btnSend = Button::create("btn_like1.png");//TODO: like几
        btnSend->addClickEventListener([=](Ref* ref){
            _requestAddComment(r->getText());
        });
        btnSend->setTitleText("SEND");
        btnSend->setPosition(Vec2(layerColor->getContentSize().width*.9, layerColor->getContentSize().height/2));
        layerColor->addChild(btnSend);
    }
}


void CLayerComment::scrollViewDidScroll(cocos2d::extension::ScrollView* view)
{
}

void CLayerComment::scrollViewDidZoom(cocos2d::extension::ScrollView* view)
{
}

void CLayerComment::tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)
{
    auto tableCell = dynamic_cast<CCommentCell*>(cell);
    if (!tableCell)
    {
        return;
    }
}

cocos2d::Size CLayerComment::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    return Size(m_winSize.width, m_fTableViewHeight/COMMENT_CELL_SIZE);
}

cocos2d::extension::TableViewCell* CLayerComment::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    TableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = CCommentCell::create();
        cell->setContentSize(tableCellSizeForIndex(table,idx));
    }
    dynamic_cast<CCommentCell*>(cell)->updateCell(static_cast<int>(idx));
    return cell;
}

ssize_t CLayerComment::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
    auto data = CDataManager::getInstance()->getDataJournal()->getJournalComments();
    return data.size();
}


void CLayerComment::setJournalId(int journalId)
{
    m_iJournalId = journalId;
}



void CLayerComment::_requestAddComment(std::string text)
{
    Json::Value root;
    root["journal_id"] = m_iJournalId;
    Json::Value content;
    content["text"] = text;
    root["content"] = buildJson(content);
    string strJson = buildJson(root);
    CHttpManager::getInstance()->HttpPost(eHttpType::comment_add, strJson);
}
