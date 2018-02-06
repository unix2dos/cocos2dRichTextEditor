//
//  JournalsCell.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/5.
//


#include "Config.h"
#include "CommonUtils.h"
#include "LayerJournals.h"
#include "JournalsCell.h"

CJournalsCell::CJournalsCell()
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




void CJournalsCell::updateCell(const std::vector<Journal_Info>&info, int idx)
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
    
    
    auto labelTime = Label::createWithTTF(getTimeString(data.createTime), MY_FONT_ENGLISH, 20);
    labelTime->setPosition(Vec2(30, getContentSize().height* .7 + 40));
    labelTime->setTextColor(Color4B(114,114,114,255));
    labelTime->setAnchorPoint(Vec2(0, 0.5));
    this->addChild(labelTime);
    

    auto labelTitle = Label::createWithTTF(data.strTitle, MY_FONT_ENGLISH, 30);
    labelTitle->setPosition(Vec2(30, getContentSize().height* .7));
    labelTitle->setTextColor(Color4B(0,0,0,255));
    labelTitle->setAnchorPoint(Vec2(0, 0.5));
    labelTitle->enableBold();
    this->addChild(labelTitle);
    

    auto labelPreview = Label::createWithTTF(data.strPreview, MY_FONT_ENGLISH, 20);
    labelPreview->setPosition(Vec2(30, getContentSize().height* .7 - 40));
    labelPreview->setTextColor(Color4B(114,114,114,255));
    labelPreview->setAnchorPoint(Vec2(0, 1));
    labelPreview->setLineSpacing(10);
    labelPreview->setDimensions(getContentSize().width* .8, getContentSize().height* .4);
    this->addChild(labelPreview);
}

