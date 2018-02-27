//
//  RichViewManager.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/10.
//

#include "Journal.h"
#include "Define.h"
#include "CommonUtils.h"
#include "HttpManager.h"
#include "DataManager.h"
#include "DataJournal.h"
#include "RichViewManager.h"


CRichViewManager* CRichViewManager::m_pInstance = nullptr;

CRichViewManager::CRichViewManager()
{
}
CRichViewManager::~CRichViewManager()
{
}

void CRichViewManager::initRichView()
{
    m_richviewType = RichViewType::none;
}

void CRichViewManager::newJournal()
{
    m_bakInfo = m_journalInfo = Journal_Info();
    m_richviewType = RichViewType::write;
}

void CRichViewManager::showJournal(const Journal_Info& info, bool myself)
{
    m_bakInfo = m_journalInfo = info;
    m_richviewType = myself? RichViewType::show_self : RichViewType::show_others;
}

void CRichViewManager::closeJournal()
{
    //对比两个info, 有更改才会请求
    bool bChange = false;
    do {
        if (m_bakInfo.isPublic != m_journalInfo.isPublic)
        {
            bChange = true;
            break;
        }
        if (m_bakInfo.strTitle != m_journalInfo.strTitle)
        {
            bChange = true;
            break;
        }
        if (m_bakInfo.strContent != m_journalInfo.strContent)
        {
            bChange = true;
            break;
        }
    }while(0);
    
    
    if (bChange)
    {
        auto dataJournal = CDataManager::getInstance()->getDataJournal();
        if (m_richviewType == RichViewType::write)
        {
            dataJournal->requestAddJournal(m_journalInfo);
        }
        else if (m_richviewType == RichViewType::show_self)
        {
            dataJournal->requestUpdateJournal(m_journalInfo);
        }
    }

    m_richviewType = RichViewType::none;
}


Journal_Info& CRichViewManager::getJournal()
{
    return m_journalInfo;
}

RichViewType CRichViewManager::getRichViewType()
{
    return m_richviewType;
}
