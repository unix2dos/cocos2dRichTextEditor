//
//  SceneLaunch.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/3.
//

USING_NS_CC;
#include "SceneBase.h"
#include "SceneManager.h"
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
    //TODO: 这是启动页面
    scheduleOnce([](float dt){
        CSceneManager::jumpToScene(eSceneType::main);
    }, 1.0f, "abc");
    return true;
}
