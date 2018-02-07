//
//  HttpDefine.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/7.
//

#include "Config.h"
#include "HttpManager.h"
#include "HttpDefine.h"


CDataHttpDelegate::CDataHttpDelegate()
{
    CHttpManager::getInstance()->registerCallBack(this);
}

CDataHttpDelegate::~CDataHttpDelegate()
{
    CHttpManager::getInstance()->unregisterCallBack(this);
}
