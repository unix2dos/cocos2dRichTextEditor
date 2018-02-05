//
//  LayerArchive.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/5.
//

#include "LayerArchive.h"
#include "Config.h"


USING_NS_CC;
using namespace cocos2d::ui;
using namespace std;

CLayerArchive::CLayerArchive()
{
    
}


CLayerArchive::~CLayerArchive(){
    
}


bool CLayerArchive::init()
{
    if(!Layer::init()){
        return false;
    }
    
    _initUI();
    
    return true;
}


void CLayerArchive::_initUI()
{
    Size size = Director::getInstance()->getWinSize();
    
    
    auto label1 = Label::createWithTTF("CLayerArchive", MY_FONT_ENGLISH, 50);
    label1->setPosition(Vec2(size.width/2, size.height/2));
    label1->setTextColor(Color4B(0,0,0,255));
    this->addChild(label1);
}
