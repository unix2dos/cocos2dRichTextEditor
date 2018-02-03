//
//  SceneLaunch.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/3.
//

#include "SceneLaunch.h"
#include "SceneManager.h"
USING_NS_CC;

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
