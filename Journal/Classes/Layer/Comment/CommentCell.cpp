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

    
    auto labelReply = Label::createWithTTF("reply", MY_FONT_CHINESE, 25);
    labelReply->setPosition(Vec2(130, 25));
    labelReply->setAnchorPoint(Vec2(0, 1));
    labelReply->setTextColor(Color4B(144,144,144,255));
    this->addChild(labelReply);
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [=](Touch* touch,Event* event) {
        if (labelReply->getBoundingBox().containsPoint(labelReply->getParent()->convertTouchToNodeSpace(touch)))
        {
            auto layerComment = dynamic_cast<CLayerComment*>(this->getUserObject());
            layerComment->replyComment(idx);
        }
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, labelReply);

}
