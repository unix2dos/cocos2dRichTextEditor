//
//  SceneManager.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/3.
//


#include "Journal.h"
#include "SceneBase.h"
#include "SceneMain.h"
#include "SceneLogin.h"
#include "SceneLaunch.h"
#include "SceneManager.h"


static CSceneManager* g_CSceneManager = nullptr;

CSceneManager* CSceneManager::getInstance()
{
    if (g_CSceneManager == nullptr) {
        g_CSceneManager = new CSceneManager;
        g_CSceneManager->init();
    }
    return g_CSceneManager;
}

void CSceneManager::destroyInstance()
{
    if (g_CSceneManager) {
        g_CSceneManager->free();
        delete g_CSceneManager;
        g_CSceneManager = nullptr;
    }
}

void CSceneManager::init()
{
}

void CSceneManager::free()
{
}


CSceneManager::CSceneManager()
:m_eLastType(eSceneType::none)
,m_eCurrType(eSceneType::none)
,m_currScene(nullptr)
{
}

CSceneManager::~CSceneManager()
{
}


CSceneBase* CSceneManager::getRunSCene()
{
    return CSceneManager::getInstance()->getCurrScene();
}


CSceneBase* CSceneManager::jumpToScene(eSceneType eType)
{
    CSceneBase* pR = NULL;
    CSceneManager::getInstance()->setSceneLastType(CSceneManager::getInstance()->getSceneCurrType());
    CSceneManager::getInstance()->setSceneCurrType(eType);
    switch (eType)
    {
        case eSceneType::none:
            break;
        case eSceneType::launch:
            pR = CSceneLaunch::create();
            break;
        case eSceneType::login:
            pR = CSceneLogin::create();
            break;
        case eSceneType::main:
            pR = CSceneMain::create();
            break;
        default:
        break;
    }
    if (pR)
    {
        if(Director::getInstance()->getRunningScene() == nullptr)
        {
            Director::getInstance()->runWithScene(pR);
        }
        else
        {
            Director::getInstance()->replaceScene(pR);
        }
        CSceneManager::getInstance()->setCurrScene(pR);
    }
    return pR;
}


eSceneType CSceneManager::getSceneLastType()
{
    return m_eLastType;
}
void CSceneManager::setSceneLastType(eSceneType type)
{
    m_eLastType = type;
}

eSceneType CSceneManager::getSceneCurrType()
{
    return m_eCurrType;
}

void CSceneManager::setSceneCurrType(eSceneType type)
{
    m_eCurrType = type;
}

CSceneBase* CSceneManager::getCurrScene()
{
    return m_currScene;
}
void CSceneManager::setCurrScene(CSceneBase* scene)
{
    m_currScene = scene;
}
