//
//  CJournalExCell.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/6.
//

#include "Config.h"
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



void CJournalExCell::updateCell(int idx)
{
    this->setLocalZOrder(idx);
    this->removeAllChildren();
    
    
    if (idx < 19) //TODO: data size
    {
        auto draw = DrawNode::create();
        draw->drawLine(Point(0, 0), Point(getContentSize().width, 0), Color4F::GRAY);
        this->addChild(draw);
    }
    
    
    std::string str = StringUtils::format("%d",idx);
    auto label1 = Label::createWithTTF(str, MY_FONT_ENGLISH, 50);
    label1->setPosition(Vec2(getContentSize().width/2, getContentSize().height/2));
    label1->setTextColor(Color4B(0,0,0,255));
    this->addChild(label1);
}
