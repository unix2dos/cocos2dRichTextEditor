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
    m_journalInfo = Journal_Info();
    m_richviewType = RichViewType::write;
}

void CRichViewManager::showJournal(const Journal_Info& info, bool myself)
{
    m_journalInfo = info;
    m_richviewType = myself? RichViewType::show_self : RichViewType::show_others;
}

void CRichViewManager::closeJournal()
{
    if (m_richviewType == RichViewType::write)
    {
        requestAddJournal();
    }
    else if (m_richviewType == RichViewType::show_self)
    {
        requestUpdateJournal();
    }
}


Journal_Info& CRichViewManager::getJournal()
{
    return m_journalInfo;
}

RichViewType CRichViewManager::getRichViewType()
{
    return m_richviewType;
}


void CRichViewManager::requestAddJournal()
{
    if (m_journalInfo.strContent == "")
    {
        return;
    }
    
    if (m_journalInfo.strTitle == "")
    {
        m_journalInfo.strTitle = m_journalInfo.strContent.substr(0, m_journalInfo.strContent.find("<"));
        if (m_journalInfo.strTitle == "")
        {
            m_journalInfo.strTitle = "Journal";
        }
    }
    
    Json::Value root;
    root["tags"] = "none";
    root["title"] = m_journalInfo.strTitle;
    root["content"] = m_journalInfo.strContent;
    root["published"] = m_journalInfo.isPublic ? "1" : "0";
    string strJson = buildServeJson(root);
    CHttpManager::getInstance()->HttpPost(eHttpType::journal_add, strJson);
}


void CRichViewManager::requestUpdateJournal()
{
    Json::Value root;
    root["id"] = m_journalInfo.strId;
    root["tags"] = "none";
    root["title"] = m_journalInfo.strTitle;
    root["content"] = m_journalInfo.strContent;
    root["published"] = m_journalInfo.isPublic ? "1" : "0";
    string strJson = buildServeJson(root);
    CHttpManager::getInstance()->HttpPost(eHttpType::journal_update, strJson);
}
