//
//  CJournalExCell.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/6.
//

#include "Journal.h"
#include "Define.h"
#include "CommonUtils.h"
#include "DataJournal.h"
#include "LayerComment.h"
#include "HttpManager.h"
#include "LayerJournalEx.h"
#include "JournalExCell.h"


CJournalExCell::CJournalExCell()
{
}


CJournalExCell::~CJournalExCell()
{
}


void CJournalExCell::onEnter()
{
    TableViewCell::onEnter();
    
}


void CJournalExCell::onExit()
{
    TableViewCell::onExit();
}


bool CJournalExCell::init()
{
    if (!TableViewCell::init())
    {
        return false;
    }
    m_winSize = Director::getInstance()->getWinSize();
    return true;
}



void CJournalExCell::updateCell(const std::vector<Journal_Info>&info, int idx)
{
    this->setLocalZOrder(idx);
    this->removeAllChildren();
    
    
    if (idx < info.size()-1)
    {
        auto draw = DrawNode::create();
        draw->drawLine(Point(0, 0), Point(getContentSize().width, 0), Color4F::GRAY);
        this->addChild(draw);
    }
    
    auto data = info[idx];
    
    
    auto labelTime = Label::createWithTTF(getTimeString(data.createTime), MY_FONT_CHINESE, 20);
    labelTime->setPosition(Vec2(30, getContentSize().height* .7 + 40));
    labelTime->setTextColor(Color4B(114,114,114,255));
    labelTime->setAnchorPoint(Vec2(0, 0.5));
    this->addChild(labelTime);
    
    
    auto labelTitle = Label::createWithTTF(data.strTitle, MY_FONT_CHINESE, 30);
    labelTitle->setPosition(Vec2(30, getContentSize().height* .7));
    labelTitle->setTextColor(Color4B(0,0,0,255));
    labelTitle->setAnchorPoint(Vec2(0, 0.5));
    labelTitle->enableBold();
    this->addChild(labelTitle);
    
    std::string strContext = removeHtmlTags(data.strContent);
    auto labelPreview = Label::createWithTTF(strContext, MY_FONT_CHINESE, 20);
    labelPreview->setPosition(Vec2(30, getContentSize().height* .7 - 40));
    labelPreview->setTextColor(Color4B(114,114,114,255));
    labelPreview->setAnchorPoint(Vec2(0, 1));
    labelPreview->setLineSpacing(10);
    labelPreview->setDimensions(getContentSize().width* .8, getContentSize().height* .25);
    this->addChild(labelPreview);
    
    
    auto btnLike = Button::create("btn_like1.png");
    btnLike->setPosition(Vec2(70, 30));
    this->addChild(btnLike);
    btnLike->addClickEventListener([&](Ref* r){
        //请求喜欢日志
        auto layer = dynamic_cast<CLayerJournalEx*>(this->getUserObject());
        layer->setJournalId(atoi(data.strId.c_str()));
        layer->requestLikeJournal();
    });
    
    
    auto btnComment = Button::create("btn_comment.png");
    btnComment->setPosition(Vec2(150, 30));
    this->addChild(btnComment);
    btnComment->addClickEventListener([=](Ref* r){
        //请求留言列表
        auto layer = dynamic_cast<CLayerJournalEx*>(this->getUserObject());
        layer->setJournalId(atoi(data.strId.c_str()));
        layer->requestCommentList();
    });
}
