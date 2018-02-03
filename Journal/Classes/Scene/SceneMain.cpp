//
//  SceneMain.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/3.
//

#include "SceneMain.h"
#include "LayerMain.h"
USING_NS_CC;

CSceneMain::CSceneMain()
{
    
}

CSceneMain::~CSceneMain()
{
}


bool CSceneMain::init()
{
    if (!CSceneBase::init()){
        return false;
    }
    
    auto layer = CLayerMain::create();
    this->addChild(layer);
    
    return true;
}
