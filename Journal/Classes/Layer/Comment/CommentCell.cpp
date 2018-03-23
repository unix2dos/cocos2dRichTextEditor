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

    
    auto avater = Sprite::create("avatar_default.png");
    avater->setPosition(Vec2(20, getContentSize().height - 30));
    avater->setScale(0.5f);
    avater->setAnchorPoint(Vec2(0, 1));
    this->addChild(avater);

    auto data = CDataManager::getInstance()->getDataJournal()->getJournalComments()[idx];
    
    auto labelName = Label::createWithTTF(data.strUserAlias, MY_FONT_CHINESE, 30);
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

    
    auto labelLike = Label::createWithTTF("like", MY_FONT_CHINESE, 25);
    labelLike->setPosition(Vec2(130, 35));
    labelLike->setAnchorPoint(Vec2(0, 1));
    labelLike->setTextColor(Color4B(144,144,144,255));
    this->addChild(labelLike);
    
    
    auto labelReply = Label::createWithTTF("reply", MY_FONT_CHINESE, 25);
    labelReply->setPosition(Vec2(230, 35));
    labelReply->setAnchorPoint(Vec2(0, 1));
    labelReply->setTextColor(Color4B(144,144,144,255));
    this->addChild(labelReply);
    
    
    auto Comment = dynamic_cast<CLayerComment*>(this->getUserObject());
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [=](Touch* touch,Event* event) {
        
        if (labelReply->getBoundingBox().containsPoint(labelReply->getParent()->convertTouchToNodeSpace(touch)))
        {
            Comment->replyComment(idx);
        }
        else if (labelLike->getBoundingBox().containsPoint(labelLike->getParent()->convertTouchToNodeSpace(touch)))
        {
            Comment->likeComment(idx);
        }
        
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, labelReply);

}
