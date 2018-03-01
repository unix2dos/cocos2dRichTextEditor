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
        
        auto content = parseJson(it["content"].asString());
        if (content.isObject())
        {
            info.strContent = content["text"].asString();
        }
 
        info.createTime = atoi(it["timestamp_create"].asString().c_str());
        info.isPublic = atoi(it["published"].asString().c_str());
        m_vecJournals.push_back(info);
    }
    
    NotificationManager::getInstance()->notify(NOTIFY_TYPE::journal_data_change);
}

void CDataJournal::parseArchives(HttpResponseInfo rep)
{
    m_vecArchives.clear();
    auto data = rep.jsonRoot["data"];
//    auto archives = data["journals"];
//    for (auto& it : archives)
//    {
//        Journal_Info info;
//        info.strId = it["id"].asString();
//        info.strTitle = it["title"].asString();
//
//        auto content = parseJson(it["content"].asString());
//        if (content.isObject())
//        {
//            info.strContent = content["text"].asString();
//        }
//
//        info.createTime = atoi(it["timestamp_create"].asString().c_str());
//        info.isPublic = atoi(it["published"].asString().c_str());
//        m_vecArchives.push_back(info);
//    }
}

void CDataJournal::parseJournalsEx(HttpResponseInfo rep)
{
    m_vecJournalsEx.clear();
    auto journals = rep.jsonRoot["data"];
    for (auto& it : journals)
    {
        Journal_Info info;
        info.strId = it["id"].asString();
        info.strTitle = it["title"].asString();
        
        auto content = parseJson(it["content"].asString());
        if (content.isObject())
        {
            info.strContent = content["text"].asString();
        }
        
        info.createTime = atoi(it["timestamp_create"].asString().c_str());
        info.modifyTime = atoi(it["timestamp_update"].asString().c_str());
        info.isPublic = atoi(it["published"].asString().c_str());
        m_vecJournalsEx.push_back(info);
    }
}




void CDataJournal::parseAddJournal(HttpResponseInfo rep)
{
    auto it = rep.jsonRoot["data"];
    Journal_Info info;
    info.strId = it["id"].asString();
    info.strTitle = it["title"].asString();
    
    auto content = parseJson(it["content"].asString());
    if (content.isObject())
    {
        info.strContent = content["text"].asString();
    }
    
    info.createTime = atoi(it["timestamp_create"].asString().c_str());
    info.modifyTime = atoi(it["timestamp_update"].asString().c_str());
    info.isPublic = atoi(it["published"].asString().c_str());
    m_vecJournals.push_back(info);
    
    NotificationManager::getInstance()->notify(NOTIFY_TYPE::journal_data_change);
}



void CDataJournal::parseUpdateJournal(HttpResponseInfo rep)
{
    auto it = rep.jsonRoot["data"];
    Journal_Info info;
    info.strId = it["id"].asString();
    info.strTitle = it["title"].asString();
    
    auto content = parseJson(it["content"].asString());
    if (content.isObject())
    {
        info.strContent = content["text"].asString();
    }
    
    info.createTime = atoi(it["timestamp_create"].asString().c_str());
    info.modifyTime = atoi(it["timestamp_update"].asString().c_str());
    info.isPublic = atoi(it["published"].asString().c_str());
    
    for (auto& it : m_vecJournals) {
        if (it.strId == info.strId) {
            it = info;
            break;
        }
    }

    NotificationManager::getInstance()->notify(NOTIFY_TYPE::journal_data_change);
}


void CDataJournal::parseCommentsList(HttpResponseInfo rep)
{
    m_vecComments.clear();
    auto comments = rep.jsonRoot["data"];
    for (auto& it : comments)
    {
        Comment_Info info;
        info.strId = it["id"].asString();
        auto content = parseJson(it["content"].asString());
        if (content.isObject())
        {
            info.strContent = content["text"].asString();
        }
        info.strJournalId = it["journal_id"].asString();
        
        
        info.strUserId = it["user_id"].asString();
        info.strUserAlias = it["Commenter_alias"].asString();
        
        info.strReplyCommentId = it["target_comment_id"].asString();
        info.strReplyUserId = it["target_user_id"].asString();
        info.srtReplyUserAlias = it["Targeter_alias"].asString();
    
        info.createTime = atoi(it["timestamp_create"].asString().c_str());
        info.modifyTime = atoi(it["timestamp_update"].asString().c_str());
    
        m_vecComments.push_back(info);
    }
}


void CDataJournal::parseCommentAdd(HttpResponseInfo rep)
{
    auto it = rep.jsonRoot["data"];
    
    Comment_Info info;
    info.strId = it["id"].asString();
    auto content = parseJson(it["content"].asString());
    if (content.isObject())
    {
        info.strContent = content["text"].asString();
    }
    info.strJournalId = it["journal_id"].asString();
    
    
    info.strUserId = it["user_id"].asString();
    info.strUserAlias = it["Commenter_alias"].asString();
    
    info.strReplyCommentId = it["target_comment_id"].asString();
    info.strReplyUserId = it["target_user_id"].asString();
    info.srtReplyUserAlias = it["Targeter_alias"].asString();
    
    info.createTime = atoi(it["timestamp_create"].asString().c_str());
    info.modifyTime = atoi(it["timestamp_update"].asString().c_str());
    
    m_vecComments.push_back(info);
}







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
    std::string str = "/jid=" + journalId;
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
    Json::Value content;
    content["text"] = text;
    root["content"] = buildJson(content);
    string strJson = buildJson(root);
    CHttpManager::getInstance()->HttpPost(eHttpType::comment_add, strJson);
}


void CDataJournal::requestReplyComment(std::string userId, std::string commentId, std::string text)
{
    if (text == "")
    {
        return;
    }
    Json::Value root;
    root["journal_id"] = m_strJournalId;
    Json::Value content;
    content["text"] = text;
    root["content"] = buildJson(content);
    root["target_user_id"] = userId;
    root["target_comment_id"] = commentId;
    string strJson = buildJson(root);
    CHttpManager::getInstance()->HttpPost(eHttpType::comment_reply, strJson);
}

void CDataJournal::requestLikeJournal(std::string journalId)
{
    Json::Value root;
    root["journal_id"] = journalId;
    root["comment_id"] = "-1";
    string strJson = buildJson(root);
    CHttpManager::getInstance()->HttpPost(eHttpType::like_add, strJson);
}


void CDataJournal::requestLikeComment(std::string commentId)
{
    Json::Value root;
    root["journal_id"] = "-1";
    root["comment_id"] = commentId;
    string strJson = buildJson(root);
    CHttpManager::getInstance()->HttpPost(eHttpType::like_add, strJson);
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
    root["tags"] = "none";
    root["title"] = info_bak.strTitle;
    
    Json::Value content;
    content["text"] = info_bak.strContent;
    root["content"] = buildJson(content);
    
    
    root["published"] = info_bak.isPublic ? "1" : "0";
    string strJson = buildJson(root);
    CHttpManager::getInstance()->HttpPost(eHttpType::journal_add, strJson);
}


void CDataJournal::requestUpdateJournal(const Journal_Info& info)
{
    Json::Value root;
    root["id"] = info.strId;
    root["tags"] = "none";
    root["title"] = info.strTitle;
    
    Json::Value content;
    content["text"] = info.strContent;
    root["content"] = buildJson(content);
    
    root["published"] = info.isPublic ? "1" : "0";
    string strJson = buildJson(root);
    CHttpManager::getInstance()->HttpPost(eHttpType::journal_update, strJson);
}
