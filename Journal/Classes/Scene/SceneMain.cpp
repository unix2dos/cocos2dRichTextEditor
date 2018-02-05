//
//  SceneMain.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/3.
//


#include "Config.h"
#include "SceneBase.h"
#include "LayerMain.h"
#include "SceneMain.h"

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
