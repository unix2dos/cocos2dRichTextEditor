//
//  DataJournal.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/6.
//

#include "Journal.h"
#include "Define.h"
#include "HttpManager.h"
#include "NotificationManager.h"
#include "CommonUtils.h"
#include "DataJournal.h"
using namespace std;

CDataJournal::CDataJournal()
:m_strJournalId("")
{
}

CDataJournal::~CDataJournal()
{
}


const std::vector<Journal_Info>& CDataJournal::getJournals()
{
    return m_vecJournals;
}

const std::vector<Journal_Info>& CDataJournal::getArchives()
{
    return m_vecArchives;
}

const std::vector<Journal_Info>& CDataJournal::getJournalsEx()
{
    return m_vecJournalsEx;
}

const std::vector<Comment_Info>& CDataJournal::getJournalComments()
{
    return m_vecComments;
}






void CDataJournal::parseJournalsData(HttpResponseInfo rep)
{
    m_vecJournals.clear();
    auto data = rep.jsonRoot["data"];
    auto journals = data["journals"];
    for (auto& it : journals)
    {
        Journal_Info info;
        info.strId = it["id"].asString();
        info.strTitle = it["title"].asString();
        info.strContent = it["content"].asString();
        info.isPublic = atoi(it["public"].asString().c_str());
        info.isLike = atoi(it["like_by_me"].asString().c_str());
        info.lickCount = atoi(it["like_count"].asString().c_str());
        info.createTime = atoi(it["create_time"].asString().c_str());
        info.modifyTime = atoi(it["update_time"].asString().c_str());
        m_vecJournals.push_back(info);
    }
    
    NotificationManager::getInstance()->notify(NOTIFY_TYPE::journal_data_change);
}


void CDataJournal::parseAddJournal(HttpResponseInfo rep)
{
    auto it = rep.jsonRoot["data"]["journal"];
    Journal_Info info;
    info.strId = it["id"].asString();
    info.strTitle = it["title"].asString();
    info.strContent = it["content"].asString();
    info.isPublic = atoi(it["public"].asString().c_str());
    info.isLike = atoi(it["liked_by_me"].asString().c_str());
    info.lickCount = atoi(it["like_count"].asString().c_str());
    info.createTime = atoi(it["create_time"].asString().c_str());
    info.modifyTime = atoi(it["update_time"].asString().c_str());
    m_vecJournals.push_back(info);
    
    NotificationManager::getInstance()->notify(NOTIFY_TYPE::journal_data_change);
}



void CDataJournal::parseUpdateJournal(HttpResponseInfo rep)
{
    auto it = rep.jsonRoot["data"]["journal"];
    Journal_Info info;
    info.strId = it["id"].asString();
    info.strTitle = it["title"].asString();
    info.strContent = it["content"].asString();
    info.isPublic = atoi(it["public"].asString().c_str());
    info.isLike = atoi(it["liked_by_me"].asString().c_str());
    info.lickCount = atoi(it["like_count"].asString().c_str());
    info.createTime = atoi(it["create_time"].asString().c_str());
    info.modifyTime = atoi(it["update_time"].asString().c_str());
    
    for (auto& it : m_vecJournals) {
        if (it.strId == info.strId) {
            it = info;
            break;
        }
    }
    
    NotificationManager::getInstance()->notify(NOTIFY_TYPE::journal_data_change);
}





void CDataJournal::parseArchives(HttpResponseInfo rep)
{
    m_vecArchives.clear();
    auto archives = rep.jsonRoot["data"]["journals"];
    for (auto& it : archives)
    {
        Journal_Info info;
        info.strId = it["id"].asString();
        info.strTitle = it["title"].asString();
        info.strContent = it["content"].asString();
        info.isPublic = atoi(it["published"].asString().c_str());
        info.isLike = atoi(it["liked_by_me"].asString().c_str());
        info.lickCount = atoi(it["like_count"].asString().c_str());
        info.createTime = atoi(it["create_time"].asString().c_str());
        info.modifyTime = atoi(it["update_time"].asString().c_str());
        m_vecArchives.push_back(info);
    }
}

void CDataJournal::parseJournalsEx(HttpResponseInfo rep)
{
    m_vecJournalsEx.clear();
    auto journals = rep.jsonRoot["data"]["journals"];
    for (auto& it : journals)
    {
        Journal_Info info;
        info.strId = it["id"].asString();
        info.strTitle = it["title"].asString();
        info.strContent = it["content"].asString();
        info.isPublic = atoi(it["published"].asString().c_str());
        info.isLike = atoi(it["liked_by_me"].asString().c_str());
        info.lickCount = atoi(it["like_count"].asString().c_str());
        info.createTime = atoi(it["create_time"].asString().c_str());
        info.modifyTime = atoi(it["update_time"].asString().c_str());
        
        m_vecJournalsEx.push_back(info);
    }
}







void CDataJournal::parseCommentsList(HttpResponseInfo rep)
{
    m_vecComments.clear();
    auto comments = rep.jsonRoot["data"]["comments"];
    for (auto& it : comments)
    {
        Comment_Info info;
        info.strId = it["id"].asString();
        info.strContent = it["content"].asString();
        info.strJournalId = it["journal_id"].asString();
        info.strUserAlias = it["user_alias"].asString();
        info.strReplyUserAlias = it["reply_user_alias"].asString();
    
        info.createTime = atoi(it["create_time"].asString().c_str());
        info.modifyTime = atoi(it["update_time"].asString().c_str());
    
        m_vecComments.push_back(info);
    }
}


void CDataJournal::parseCommentAdd(HttpResponseInfo rep)
{
    auto it = rep.jsonRoot["data"]["comment"];
    
    Comment_Info info;
    info.strId = it["id"].asString();
    info.strContent = it["content"].asString();
    info.strJournalId = it["journal_id"].asString();
    info.strUserAlias = it["user_alias"].asString();
    info.strReplyUserAlias = it["reply_user_alias"].asString();

    info.createTime = atoi(it["create_time"].asString().c_str());
    info.modifyTime = atoi(it["update_time"].asString().c_str());
    
    m_vecComments.push_back(info);
}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CDataJournal::requestArchive()
{
    CHttpManager::getInstance()->HttpGet(eHttpType::archive_get);
}

void CDataJournal::requestJournalsEx()
{
    CHttpManager::getInstance()->HttpGet(eHttpType::journal_recommend);
}

void CDataJournal::requestCommentList(std::string journalId)
{
    m_strJournalId = journalId;
    std::string str = "?JournalId=" + journalId;
    CHttpManager::getInstance()->HttpGet(eHttpType::comment_list, str);
}

void CDataJournal::requestAddComment(std::string text)
{
    if (text == "")
    {
        return;
    }
    Json::Value root;
    root["journal_id"] = m_strJournalId;
    root["content"] = text;
    string strJson = buildJson(root);
    CHttpManager::getInstance()->HttpPost(eHttpType::comment_add, strJson);
}


void CDataJournal::requestReplyComment(std::string commentId, std::string text)
{
    if (text == "")
    {
        return;
    }
    Json::Value root;
    root["journal_id"] = m_strJournalId;
    root["content"] = text;
    root["reply_comment_id"] = commentId;
    string strJson = buildJson(root);
    CHttpManager::getInstance()->HttpPost(eHttpType::comment_add, strJson);
}

void CDataJournal::requestAddLikeJournal(std::string journalId)
{
    Json::Value root;
    root["like_type"] = "1";
    root["like_id"] = journalId;
    string strJson = buildJson(root);
    CHttpManager::getInstance()->HttpPost(eHttpType::like_add, strJson);
}


void CDataJournal::requestDelLikeJournal(std::string journalId)
{
    Json::Value root;
    root["like_type"] = "1";
    root["like_id"] = journalId;
    string strJson = buildJson(root);
    CHttpManager::getInstance()->HttpPost(eHttpType::like_delete, strJson);
}


void CDataJournal::requestLikeComment(std::string commentId)
{
    Json::Value root;
    root["like_type"] = "2";
    root["like_id"] = commentId;
    string strJson = buildJson(root);
    CHttpManager::getInstance()->HttpPost(eHttpType::like_add, strJson);
}



void CDataJournal::requestJournallist()
{
    CHttpManager::getInstance()->HttpGet(eHttpType::journal_list);
}

void CDataJournal::requestAddJournal(const Journal_Info& info)
{
    Journal_Info info_bak = info;
    if (info_bak.strContent == "")
    {
        return;
    }
    
    if (info_bak.strTitle == "")
    {
        info_bak.strTitle = info_bak.strContent.substr(0, info_bak.strContent.find("<"));
        if (info_bak.strTitle == "")
        {
            info_bak.strTitle = "Journal";
        }
    }
    
    Json::Value root;
    root["title"] = info_bak.strTitle;
    root["content"] = info_bak.strContent;
    root["public"] = info_bak.isPublic ? "1" : "0";
    string strJson = buildJson(root);
    CHttpManager::getInstance()->HttpPost(eHttpType::journal_add, strJson);
}


void CDataJournal::requestUpdateJournal(const Journal_Info& info)
{
    Json::Value root;
    root["id"] = info.strId;
    root["title"] = info.strTitle;
    root["content"] = info.strContent;
    root["public"] = info.isPublic ? "1" : "0";
    string strJson = buildJson(root);
    CHttpManager::getInstance()->HttpPost(eHttpType::journal_update, strJson);
}


void CDataJournal::requestDeleteJournal(std::string journalId)
{
    Json::Value root;
    root["id"] = journalId;
    string strJson = buildJson(root);
    CHttpManager::getInstance()->HttpPost(eHttpType::journal_delete, strJson);
    
    //假想已经删除成功, 因为要立即显示
    for (auto it = m_vecJournals.begin(); it != m_vecJournals.end(); ++it)
    {
        if (it->strId == journalId)
        {
            m_vecJournals.erase(it);
            NotificationManager::getInstance()->notify(NOTIFY_TYPE::journal_data_change);
            break;
        }
    }

}
