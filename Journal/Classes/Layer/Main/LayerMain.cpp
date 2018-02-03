//
//  LayerMain.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/3.
//

#include "LayerMain.h"
USING_NS_CC;

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
}
