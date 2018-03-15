//
//  DataUser.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/6.
//

#include "Journal.h"
#include "Define.h"
#include "HttpManager.h"
#include "CommonUtils.h"
#include "DataUser.h"


CDataUser::CDataUser()
{
}

CDataUser::~CDataUser()
{
    
}

void CDataUser::parseServeData(HttpResponseInfo rep)
{
    auto data = rep.jsonRoot["data"];
    auto user = data["user"];
    m_userInfo.email = user["email"].asString();
    m_userInfo.avatar = user["avatar"].asString();
    m_userInfo.alias = user["alias"].asString();
}


const User_Info& CDataUser::getUserInfo()
{
    return m_userInfo;
}


void CDataUser::requestSignUp(std::string strEmail, std::string strPass, std::string strAlias)
{
    Json::Value root;
    root["email"] = strEmail;
    root["password"] = strPass;
    root["alias"] = strAlias;
    string strJson = buildJson(root);
    CHttpManager::getInstance()->HttpPost(eHttpType::signup, strJson);
}


void CDataUser::requestLogin(std::string strEmail, std::string strPass)
{
    Json::Value root;
    root["email"] = strEmail;
    root["password"] = strPass;
    string strJson = buildJson(root);
    CHttpManager::getInstance()->HttpPost(eHttpType::login, strJson);
}
