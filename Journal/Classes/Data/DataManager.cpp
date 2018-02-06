//
//  DataManager.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/6.
//

#include "Config.h"
#include "DataUser.h"
#include "DataJournal.h"
#include "DataManager.h"


static CDataManager* g_CDataManager = nullptr;

CDataManager* CDataManager::getInstance()
{
    if (g_CDataManager == nullptr) {
        g_CDataManager = new CDataManager;
        g_CDataManager->init();
    }
    return g_CDataManager;
}

void CDataManager::destroyInstance()
{
    if (g_CDataManager) {
        g_CDataManager->free();
        delete g_CDataManager;
        g_CDataManager = nullptr;
    }
}

void CDataManager::init()
{
    m_pDataUser = new CDataUser();
    m_pDataJournal = new CDataJournal();
}

void CDataManager::free()
{
    delete m_pDataUser;
    delete m_pDataJournal;
}


CDataManager::CDataManager()
{
}

CDataManager::~CDataManager()
{
}


CDataUser* CDataManager::getDataUser()
{
    return m_pDataUser;
}

CDataJournal* CDataManager::getDataJournal()
{
    return m_pDataJournal;
}
