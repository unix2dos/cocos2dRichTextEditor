//
//  SceneLaunch.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/3.
//

#include "SceneLaunch.h"


CSceneLaunch::CSceneLaunch()
{
    
}

CSceneLaunch::~CSceneLaunch()
{
}


bool CSceneLaunch::init()
{
    if (!CSceneBase::init()){
        return false;
    }
    return true;
}
