//
//  LayerJournals.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/5.
//

#include "LayerJournals.h"
#include "RichText.h"
#include "Config.h"
#include "ui/UIButton.h"


USING_NS_CC;
using namespace cocos2d::ui;
using namespace std;

CLayerJournals::CLayerJournals()
{
    
}


CLayerJournals::~CLayerJournals(){
    
}


bool CLayerJournals::init()
{
    if(!Layer::init()){
        return false;
    }
    
    _initUI();
    
    return true;
}


void CLayerJournals::_initUI()
{
    Size size = Director::getInstance()->getWinSize();
    
    auto btn = Button::create("add.png");
    btn->setPosition(Vec2(size.width/2, size.height/2));
    btn->addClickEventListener([](Ref* r){
        CRichText::getInstance()->haha();
    });
    this->addChild(btn);
}
