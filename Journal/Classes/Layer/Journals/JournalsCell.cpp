//
//  JournalsCell.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/5.
//


#include "Journal.h"
#include "Define.h"
#include "CommonUtils.h"
#include "LayerJournals.h"
#include "DataManager.h"
#include "DataJournal.h"
#include "JournalsCell.h"

CJournalsCell::CJournalsCell()
:m_strJournalId("")
{
}


CJournalsCell::~CJournalsCell()
{
}


void CJournalsCell::onEnter()
{
    TableViewCell::onEnter();
}


void CJournalsCell::onExit()
{
    TableViewCell::onExit();
}


bool CJournalsCell::init()
{
    if (!TableViewCell::init())
    {
        return false;
    }
    m_winSize = Director::getInstance()->getWinSize();
    return true;
}


std::string CJournalsCell::getJournalId()
{
    return m_strJournalId;
}

void CJournalsCell::updateCell(const std::vector<Journal_Info>&info, int idx)
{
    this->setLocalZOrder(idx);
    this->removeAllChildren();

    
//    if (idx < info.size()-1)
    {
        auto draw = DrawNode::create();
        draw->drawLine(Point(0, 0), Point(getContentSize().width, 0), Color4F::GRAY);
        this->addChild(draw);
    }
    
    auto data = info[idx];
    m_strJournalId = data.strId;
    
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
    auto labelContext = Label::createWithTTF(strContext, MY_FONT_CHINESE, 20);
    labelContext->setPosition(Vec2(30, getContentSize().height* .7 - 40));
    labelContext->setTextColor(Color4B(114,114,114,255));
    labelContext->setAnchorPoint(Vec2(0, 1));
    labelContext->setLineSpacing(10);
    labelContext->setDimensions(getContentSize().width* .8, getContentSize().height* .35);
    this->addChild(labelContext);
    
    
    auto btnComment = Button::create("btn_comment.png");
    btnComment->setPosition(Vec2(60, 30));
    btnComment->setScale(.8f);
    this->addChild(btnComment);
    btnComment->addClickEventListener([=](Ref* r){
        //请求留言列表
        auto dataJournal = CDataManager::getInstance()->getDataJournal();
        dataJournal->requestCommentList(data.strId.c_str());
    });
}

