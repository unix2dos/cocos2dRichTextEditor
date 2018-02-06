//
//  DataUser.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/6.
//

#include "DataUser.h"


CDataUser::CDataUser()
{
    //临时数据
    m_userInfo.username = "levonfly";
}

CDataUser::~CDataUser()
{
    
}


const User_Info& CDataUser::getUserInfo()
{
    return m_userInfo;
}
