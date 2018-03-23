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


CLayerComment::CLayerComment()
:m_pTableView(nullptr)
,m_fTableViewHeight(0.0f)
,m_type(CommentType::none)
,m_editBox(nullptr)
,m_strReplyCommentId("")
,m_strPlaceholder("")
{
    
}


CLayerComment::~CLayerComment(){
    
}


bool CLayerComment::init()
{
    if(!Layer::init()){
        return false;
    }
    
    return true;
}


void CLayerComment::onEnter()
{
    Layer::onEnter();
    _initUI();
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
    
    //伪导航栏
    auto btnBack = Button::create("ui_back.png");
    btnBack->setPosition(Vec2(30, m_fTableViewHeight-COMMENT_NAV_HEIGHT/2));
    this->addChild(btnBack);
    btnBack->addClickEventListener([&](Ref* r){
        this->removeFromParent();
    });
    auto label = Label::createWithTTF("COMMENT", MY_FONT_CHINESE, 30);
    label->setPosition(Vec2(m_winSize.width/2, m_fTableViewHeight-COMMENT_NAV_HEIGHT/2));
    label->setTextColor(Color4B(0,0,0,255));
    this->addChild(label);
    
    //减去伪导航栏
    m_fTableViewHeight -= COMMENT_NAV_HEIGHT;
    
    //减去评论栏
    int inputHeight = 0;
    //    if (m_type != CommentType::self)
    {
        inputHeight = COMMENT_INPUT_HEIGHT;
    }
    m_fTableViewHeight -= inputHeight;
    
    //tableview
    m_pTableView = TableView::create(this, Size(m_winSize.width, m_fTableViewHeight));
    m_pTableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
    m_pTableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    m_pTableView->setDelegate(this);
    m_pTableView->setPositionY(inputHeight);
    this->addChild(m_pTableView);
    m_pTableView->reloadData();
    
    
    //评论框
    auto layerColor = LayerColor::create(Color4B(240, 240, 240, 255), m_winSize.width, inputHeight);
    this->addChild(layerColor);
    
    auto node = Node::create();
    auto pBack = Sprite::create("login_input.png");
    node->addChild(pBack);
    
    auto editBoxSize = Size(480, 70);
    m_editBox = ui::EditBox::create(editBoxSize, ui::Scale9Sprite::create());
    m_editBox->setPlaceHolder("add comment");
    m_editBox->setPlaceholderFontSize(40);
    m_editBox->setPlaceholderFontColor(Color3B::GRAY);
    m_editBox->setFontColor(Color3B::BLACK);
    m_editBox->setFontSize(40);
    node->addChild(m_editBox);
    node->setPosition(Vec2(layerColor->getContentSize().width/2, layerColor->getContentSize().height/2));
    layerColor->addChild(node);
    
    auto btnSend = Button::create("btn_like1.png");//TODO: 用个其他图片
    btnSend->addClickEventListener([=](Ref* ref){
        _addComment();
    });
    btnSend->setTitleText("SEND");
    btnSend->setPosition(Vec2(layerColor->getContentSize().width*.9, layerColor->getContentSize().height/2));
    layerColor->addChild(btnSend);
    
    
    setCommentType(CommentType::add);
}


//请求添加评论
void CLayerComment::_addComment()
{
    auto dataJournal = CDataManager::getInstance()->getDataJournal();
    if (m_type == CommentType::add)
    {
        dataJournal->requestAddComment(m_editBox->getText());
    }
    else if (m_type == CommentType::reply)
    {
        std::string text = m_editBox->getText();
        if (text.size() > m_strPlaceholder.size() && text.substr(0,m_strPlaceholder.size()) == m_strPlaceholder)
        {
            text = text.substr(m_strPlaceholder.size());
        }
        dataJournal->requestReplyComment(m_strReplyCommentId, text);
    }
    //置空
    m_editBox->setText("");
    
    //重置状态
    setCommentType(CommentType::add);
}

void CLayerComment::replyComment(int idx)
{
    setCommentType(CommentType::reply);
    
    auto data = CDataManager::getInstance()->getDataJournal()->getJournalComments()[idx];
    m_strPlaceholder = "@" + data.strUserAlias + ": ";
    m_editBox->setText(m_strPlaceholder.c_str());
    
    m_strReplyCommentId = data.strId;
}


void CLayerComment::likeComment(int idx)
{
    auto dataJorunal = CDataManager::getInstance()->getDataJournal();
    auto data = dataJorunal->getJournalComments()[idx];
    dataJorunal->requestLikeComment(data.strId);
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
    auto data = CDataManager::getInstance()->getDataJournal()->getJournalComments()[idx];
    auto labelContent = Label::createWithTTF(data.strContent, MY_FONT_CHINESE, 30);
    labelContent->setDimensions(m_winSize.width-COMMENT_WIDTH_OFFSET, 0);
    auto height = labelContent->getContentSize().height;
    //    log("height %ld %f",  idx, height);
    if (height < COMMENT_HEIGHT_MIN)
    {
        height = COMMENT_HEIGHT_MIN;//不足最小高度, 因为有头像
    }

    height += COMMENT_HEIGHT_PADDING;//加延长,还要加用户名高度

    return Size(m_winSize.width, height);
}

cocos2d::extension::TableViewCell* CLayerComment::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    TableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = CCommentCell::create();
    }
    cell->setUserObject(this);
    cell->setContentSize(tableCellSizeForIndex(table,idx));
    dynamic_cast<CCommentCell*>(cell)->updateCell(static_cast<int>(idx));
    return cell;
}

ssize_t CLayerComment::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
    auto data = CDataManager::getInstance()->getDataJournal()->getJournalComments();
    return data.size();
}



void CLayerComment::endWithHttpData(eHttpType myType, HttpResponseInfo rep)
{
    if (myType == eHttpType::comment_add)
    {
        if (rep.status == eHttpStatus::success)
        {
            m_pTableView->reloadData();
            
            float totalHeight = 0;
            for (int i = 0; i < numberOfCellsInTableView(m_pTableView); ++i)
            {
                totalHeight += tableCellSizeForIndex(m_pTableView, i).height;
            }
            if (totalHeight >= m_fTableViewHeight)
            {
                m_pTableView->setContentOffset(Vec2(0,m_pTableView->maxContainerOffset().y));
            }
        }
    }
}


void CLayerComment::setCommentType(CommentType type)
{
    m_type = type;
}
