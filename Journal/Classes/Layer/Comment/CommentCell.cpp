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
#include "LayerComment.h"
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

//    {
//        auto draw = DrawNode::create();
//        draw->drawLine(Point(0, getContentSize().height), Point(getContentSize().width, getContentSize().height), Color4F::GRAY);
//        this->addChild(draw);
//    }
//    {
//        auto draw = DrawNode::create();
//        draw->drawLine(Point(0, 0), Point(getContentSize().width, 0), Color4F::GRAY);
//        this->addChild(draw);
//    }

    
    auto avater = Sprite::create("avatar_default.png");
    avater->setPosition(Vec2(20, getContentSize().height - 30));
    avater->setScale(0.5f);
    avater->setAnchorPoint(Vec2(0, 1));
    this->addChild(avater);

    auto data = CDataManager::getInstance()->getDataJournal()->getJournalComments()[idx];
    auto labelName = Label::createWithTTF(data.strUserId, MY_FONT_CHINESE, 30);
    labelName->setPosition(Vec2(130, getContentSize().height - 40));
    labelName->setTextColor(Color4B(0,0,0,255));
    labelName->setAnchorPoint(Vec2(0, 1));
    labelName->enableBold();
    this->addChild(labelName);
    
    
    auto labelContent = Label::createWithTTF(data.strContent, MY_FONT_CHINESE, 30);
    labelContent->setPosition(Vec2(130, getContentSize().height - 90));
    labelContent->setTextColor(Color4B(0,0,0,255));
    labelContent->setAnchorPoint(Vec2(0, 1));
    labelContent->setDimensions(getContentSize().width - COMMENT_WIDTH_OFFSET, 0);
    labelContent->setOverflow(Label::Overflow::RESIZE_HEIGHT);
    this->addChild(labelContent);

    //    auto a = labelContent->getBoundingBox();
    //    auto b = labelContent->getContentSize();
    //    log("width %f height %f\n", labelContent->getWidth(), labelContent->getHeight());
    //    log("size %f %f\n", labelContent->getDimensions().width, labelContent->getDimensions().height);
    //    log("a %f %f\n", a.size.width, a.size.height);
    //    log("b %f %f\n", b.width, b.height);
    //    log("b %d %f \n",idx, b.height);
    

    
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
