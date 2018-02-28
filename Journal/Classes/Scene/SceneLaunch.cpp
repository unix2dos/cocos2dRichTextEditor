//
//  SceneLaunch.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/3.
//

#include "Journal.h"
#include "Define.h"
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
    
    auto layer = LayerColor::create(Color4B(255,255,255,255));
    this->addChild(layer);
    
    //先发送getinfo
    CHttpManager::getInstance()->HttpGet(eHttpType::getinfo);
    return true;
}


void CSceneLaunch::endWithHttpData(eHttpType myType, HttpResponseInfo rep)
{
    if (myType == eHttpType::getinfo)
    {
        if (rep.status == eHttpStatus::success)
        {
            CSceneManager::jumpToScene(eSceneType::main);
        }
        else if (rep.status == eHttpStatus::logicErr)
        {
            CSceneManager::jumpToScene(eSceneType::login);
        }
    }
}
