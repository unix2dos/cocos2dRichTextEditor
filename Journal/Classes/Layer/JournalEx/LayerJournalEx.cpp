//
//  LayerJournalEx.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/5.
//

#include "Config.h"
#include "LayerJournalEx.h"


CLayerJournalEx::CLayerJournalEx()
{
    
}


CLayerJournalEx::~CLayerJournalEx(){
    
}


bool CLayerJournalEx::init()
{
    if(!Layer::init()){
        return false;
    }
    
    _initUI();
    
    return true;
}


void CLayerJournalEx::_initUI()
{
    Size size = Director::getInstance()->getWinSize();
    
    auto label1 = Label::createWithTTF("CLayerJournalEx", MY_FONT_ENGLISH, 50);
    label1->setPosition(Vec2(size.width/2, 30));
    label1->setTextColor(Color4B(0,0,0,255));
    this->addChild(label1);
}
