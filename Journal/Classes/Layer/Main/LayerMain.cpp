//
//  LayerMain.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/3.
//

#include "LayerMain.h"
#include "RichText.h"
#include "ui/UIButton.h"
USING_NS_CC;
using namespace cocos2d::ui;

CLayerMain::CLayerMain(){
    
}


CLayerMain::~CLayerMain(){
    
}


bool CLayerMain::init()
{
    if(!Layer::init()){
        return false;
    }
    
    _initUI();
    
    return true;
}


void CLayerMain::_initUI()
{
    Size size = Director::getInstance()->getWinSize();
    auto bg = Sprite::create("bg.png");
    bg->setPosition(Vec2(size.width/2, size.height/2));
    this->addChild(bg);
    
    auto btn = Button::create("add.png");
    btn->setPosition(Vec2(size.width/2, size.height/2));
    btn->addClickEventListener([](Ref* r){
        CRichText::getInstance()->haha();
    });
    this->addChild(btn);
}
