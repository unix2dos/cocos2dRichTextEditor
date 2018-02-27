//
//  CommentCell.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/26.
//

#include "Journal.h"
#include "Define.h"
#include "DataManager.h"
#include "DataJournal.h"
#include "CommentCell.h"

CCommentCell::CCommentCell()
{
}


CCommentCell::~CCommentCell()
{
}


void CCommentCell::onEnter()
{
    TableViewCell::onEnter();
    
}


void CCommentCell::onExit()
{
    TableViewCell::onExit();
}


bool CCommentCell::init()
{
    if (!TableViewCell::init())
    {
        return false;
    }
    m_winSize = Director::getInstance()->getWinSize();
    return true;
}



void CCommentCell::updateCell(int idx)
{
    this->setLocalZOrder(idx);
    this->removeAllChildren();
    
    
    auto data = CDataManager::getInstance()->getDataJournal()->getJournalComments();
    
//    if (idx < 19) //TODO: data size
//    {
//        auto draw = DrawNode::create();
//        draw->drawLine(Point(getContentSize().width*0.2, 0), Point(getContentSize().width, 0), Color4F::GRAY);
//        this->addChild(draw);
//    }
    
//    auto avater = Sprite::create("avatar_default.png");
//    avater->setPosition(Vec2(getContentSize().width*0.1, getContentSize().height/2));
//    avater->setScale(0.5f);
//    this->addChild(avater);
//
//
//    std::string name = StringUtils::format("%d",idx);
//    auto labelName = Label::createWithTTF(name, MY_FONT_CHINESE, 30);
//    labelName->setPosition(Vec2(getContentSize().width*0.2, getContentSize().height/2 + 25));
//    labelName->setTextColor(Color4B(0,0,0,255));
//    labelName->setAnchorPoint(Vec2(0, 0.5));
//    this->addChild(labelName);
//
//
//    std::string email = StringUtils::format("-------------");
//    auto labelEmail = Label::createWithTTF(email, MY_FONT_CHINESE, 30);
//    labelEmail->setPosition(Vec2(getContentSize().width*0.2, getContentSize().height/2 - 25));
//    labelEmail->setTextColor(Color4B(114,114,114,255));
//    labelEmail->setAnchorPoint(Vec2(0, 0.5));
//    this->addChild(labelEmail);
//
//    auto btnRight = Button::create("btn_right.png");
//    btnRight->setPosition(Vec2(getContentSize().width*0.9, getContentSize().height/2));
//    btnRight->addClickEventListener([&](Ref* r){
//
//    });
//    this->addChild(btnRight);
}
