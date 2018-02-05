//
//  SceneBase.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/3.
//


#include "SceneBase.h"

CSceneBase::CSceneBase()
{
}

CSceneBase::~CSceneBase()
{
}

bool CSceneBase::init()
{
    if (!Scene::init()) {
        return false;
    }
    return true;
}
