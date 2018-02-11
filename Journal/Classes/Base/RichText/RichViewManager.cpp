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

void CRichViewManager::addJournal(std::string strContext)
{
    //发送请求
    Json::Value root;
    root["tags"] = "none";
    root["title"] = "none";
    
//    Json::Value content;
    //    content["text"] = strContext;//TODO:1111111111
    root["content"] = strContext;
    root["published"] = "1";
    string strJson = buildServeJson(root);
    CHttpManager::getInstance()->HttpPost(eHttpType::journal_add, strJson);
}
