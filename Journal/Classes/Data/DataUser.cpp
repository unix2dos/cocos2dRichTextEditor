//
//  DataUser.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/6.
//

#include "Journal.h"
#include "HttpManager.h"
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
    auto user = data["userinfo"];
    m_userInfo.username = user["username"].asString();
    m_userInfo.avatar = user["avatar"].asString();
    m_userInfo.alias = user["alias"].asString();
    m_userInfo.userid = user["id"].asInt();
    m_userInfo.journal_count = user["journal_count"].asInt();
    m_userInfo.likes = user["likes"].asInt();
}


const User_Info& CDataUser::getUserInfo()
{
    return m_userInfo;
}
