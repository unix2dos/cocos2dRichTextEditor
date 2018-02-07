//
//  HttpManager.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/7.
//

#include "Config.h"
#include "HttpManager.h"


static CHttpManager* g_CHttpManager = nullptr;

CHttpManager* CHttpManager::getInstance()
{
    if (g_CHttpManager == nullptr) {
        g_CHttpManager = new CHttpManager;
        g_CHttpManager->init();
    }
    return g_CHttpManager;
}

void CHttpManager::destroyInstance()
{
    if (g_CHttpManager) {
        g_CHttpManager->free();
        delete g_CHttpManager;
        g_CHttpManager = nullptr;
    }
}

void CHttpManager::init()
{
}

void CHttpManager::free()
{
}


CHttpManager::CHttpManager()
{
}

CHttpManager::~CHttpManager()
{
}


bool CHttpManager::HttpPost(string url, eHttpType myType, std::string data)
{
    return HttpSendRequest(HttpRequest::Type::POST, url, myType, data);
}
bool CHttpManager::HttpGet(string url, eHttpType myType, std::string data)
{
    return HttpSendRequest(HttpRequest::Type::GET, url, myType, data);
}

bool CHttpManager::HttpSendRequest(HttpRequest::Type type, string url, eHttpType myType, std::string data)
{
    if (m_mapHttpStatus[myType].status == eHttpStatus::Send)
    {
        return false;
    }
    m_mapHttpStatus[myType].status = eHttpStatus::Send;


    HttpRequest* request = new (std::nothrow) class HttpRequest();
    request->setRequestType(type);
    request->setUrl(url);
    request->setRequestData(data.c_str(), data.length());
    std::vector<std::string> headers = request->getHeaders();
    std::vector<std::string> commonHeaders = _getCommonHeaders();
    headers.insert(headers.end(), commonHeaders.begin(), commonHeaders.end());
    request->setHeaders(headers);
    request->setResponseCallback(CC_CALLBACK_2(CHttpManager::_onHttpRequestCompleted, this));
    request->setTag(StringUtils::format("%d", (int)myType));
    HttpClient::getInstance()->send(request);
    request->release();
 
    return true;

}

void CHttpManager::_onHttpRequestCompleted(HttpClient *sender, HttpResponse *response)
{
    if (!response)
    {
        return;
    }

    std::string status = StringUtils::format("HTTP Status Code:%ld , tag = %s", response->getResponseCode(), response->getHttpRequest()->getTag());
    log("response: %s", status.c_str());

    auto myType = static_cast<eHttpType>(atoi(response->getHttpRequest()->getTag()));
    if (!response->isSucceed())
    {
        m_mapHttpStatus[myType].status = eHttpStatus::Serr;
        m_mapHttpStatus[myType].msg = response->getErrorBuffer();
    }
    else
    {
        std::vector<char> *buffer = response->getResponseData();
        std::string strContent = "";
        strContent.assign(buffer->begin(), buffer->end());
        
        
        log("%s", strContent.c_str());
        
        //解析成Json
        
        //看ret
        
        //check err code
        

        //        CBaseLoad::LoadJsonString(m_stujson, strData);
        //
        //        if(m_stujson.isHasJson("ret"))
        //        {
        //            if (m_stujson.getValue("ret") == "0")
        //            {
        //                SetHttpOpState(type,eHttpStateBase::eHttpStateBase_Rok);
        //                SetHttpOpMsg(type, "OK");
        //            }
        //            else
        //            {
        //                SetHttpOpState(type,eHttpStateBase::eHttpStateBase_Rerr);
        //                SetHttpOpMsg(type, m_stujson.getValue("msg").c_str());
        //            }
        //        }
        //        else
        //        {
        //            success = false;
        //            SetHttpOpState(type,eHttpStateBase::eHttpStateBase_err);
        //            SetHttpOpMsg(type, GetXmlString("login_errornet"));
        //        }
    

        //
        //    //公共数据解析
        //    CDataUser::getInstance()->endWithHttpData(type, success, m_stujson);
        //
        //    if (success)
        //        checkErrorCode(type,m_stujson.getValue("ret"));
        
    }
    
    
    for (const auto& it : m_setDataRegister)
    {
        it->endWithHttpData(myType, m_mapHttpStatus[myType]);
    }
}



void CHttpManager::registerCallBack(CDataHttpDelegate* p)
{
    m_setDataRegister.insert(p);
}

void CHttpManager::unregisterCallBack(CDataHttpDelegate* p)
{
    if (m_setDataRegister.find(p) != m_setDataRegister.end())
    {
        m_setDataRegister.erase(p);
    }
}

std::vector<std::string> CHttpManager::_getCommonHeaders()
{
    std::vector<std::string> commonHeaders;
    commonHeaders.push_back("Content-Type: application/json; charset=utf-8");
    commonHeaders.push_back("Accept: application/json; charset=utf-8");
    return commonHeaders;
}
