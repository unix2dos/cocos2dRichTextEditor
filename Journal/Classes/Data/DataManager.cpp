//
//  DataManager.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/6.
//

#include "Journal.h"
#include "Define.h"
#include "DataUser.h"
#include "DataJournal.h"
#include "HttpManager.h"
#include "LayerMsg.h"
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


void CDataManager::parseServeData(eHttpType myType, HttpResponseInfo rep)
{
    //TODO: 公共错误处理, check错误码??
    if (rep.status != eHttpStatus::success)
    {
        CLayerMsg::showMsg(rep.msg);
        return;
    }
    
    switch (myType) {
        case eHttpType::getinfo:
        case eHttpType::signup:
        case eHttpType::login:
            m_pDataUser->parseServeData(rep);
            break;
        case eHttpType::journal_list:
            m_pDataJournal->parseJournalsData(rep);
            break;
        case eHttpType::journal_add:
            m_pDataJournal->parseAddJournal(rep);
            break;
        case eHttpType::journal_update:
            m_pDataJournal->parseUpdateJournal(rep);
            break;
        case eHttpType::journal_recommend:
            m_pDataJournal->parseJournalsEx(rep);
            break;
        case eHttpType::comment_list:
            m_pDataJournal->parseCommentsList(rep);
            break;
        case eHttpType::comment_add:
            m_pDataJournal->parseCommentAdd(rep);
            break;
        case eHttpType::archive_get:
            m_pDataJournal->parseArchives(rep);
            break;
        default:
            break;
    }
    
}


CDataUser* CDataManager::getDataUser()
{
    return m_pDataUser;
}

CDataJournal* CDataManager::getDataJournal()
{
    return m_pDataJournal;
}
