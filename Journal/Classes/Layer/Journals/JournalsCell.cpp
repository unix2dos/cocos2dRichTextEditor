//
//  JournalsCell.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/5.
//


#include "Config.h"
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


    std::string str = StringUtils::format("%d",idx);
    auto label1 = Label::createWithTTF(str, MY_FONT_ENGLISH, 50);
    label1->setPosition(Vec2(getContentSize().width/2, getContentSize().height/2));
    label1->setTextColor(Color4B(0,0,0,255));
    this->addChild(label1);
}

