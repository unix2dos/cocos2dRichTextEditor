//
//  SceneLogin.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/9.
//

#include "Journal.h"
#include "SceneBase.h"
#include "LayerLogin.h"
#include "SceneLogin.h"


CSceneLogin::CSceneLogin()
{
    
}

CSceneLogin::~CSceneLogin()
{
}


bool CSceneLogin::init()
{
    if (!CSceneBase::init()){
        return false;
    }
    
    auto layer = CLayerLogin::create();
    this->addChild(layer);
}
