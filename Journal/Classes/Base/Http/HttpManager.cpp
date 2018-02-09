//
//  HttpManager.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/7.
//

#include "Journal.h"
#include "CommonUtils.h"
#include "Define.h"
#include "LayerMsg.h"
#include "HttpManager.h"

//消息回调
CDataHttpDelegate::CDataHttpDelegate()
{
    CHttpManager::getInstance()->registerCallBack(this);
}

CDataHttpDelegate::~CDataHttpDelegate()
{
    CHttpManager::getInstance()->unregisterCallBack(this);
}



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

CHttpManager::CHttpManager()
{
}
CHttpManager::~CHttpManager()
{
}
void CHttpManager::init()
{
}
void CHttpManager::free()
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
    if (m_mapHttpStatus[myType].status == eHttpStatus::sending)
    {
        return false;
    }
    m_mapHttpStatus[myType].status = eHttpStatus::sending;

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
    
    log("request type = %d, data = %s\n", (int)myType, data.c_str());
 
    return true;

}

void CHttpManager::_onHttpRequestCompleted(HttpClient *sender, HttpResponse *response)
{
    if (!response)
    {
        return;
    }

//    std::string status = StringUtils::format("HTTP Status Code:%ld , tag = %s", response->getResponseCode(), response->getHttpRequest()->getTag());
//    log("response: %s", status.c_str());

    auto myType = static_cast<eHttpType>(atoi(response->getHttpRequest()->getTag()));
    if (!response->isSucceed())//发送错误
    {
        m_mapHttpStatus[myType].status = eHttpStatus::sendErr;//发送错误, 连不上服务器
        m_mapHttpStatus[myType].msg = response->getErrorBuffer();
    }
    else
    {
        std::vector<char> *buffer = response->getResponseData();
        std::string strContent = "";
        strContent.assign(buffer->begin(), buffer->end());
        
        auto root = parseServeJson(strContent);
        if (root == Json::nullValue)
        {
            m_mapHttpStatus[myType].status = eHttpStatus::serverErr;//json错误, 404, 500...
            m_mapHttpStatus[myType].msg = "server error";
        }
        else
        {
            if (root["ret"].asString() != "0")
            {
                m_mapHttpStatus[myType].status = eHttpStatus::logicErr;//逻辑错误,check错误码
            }
            else
            {
                m_mapHttpStatus[myType].status = eHttpStatus::success;//ok
            }
            m_mapHttpStatus[myType].msg = root["msg"].asString();
            m_mapHttpStatus[myType].jsonRoot = root;
        }
    }
    
    //TODO: 公共错误处理, check错误码??
    if (m_mapHttpStatus[myType].status != eHttpStatus::success)
    {
        CLayerMsg::showMsg(m_mapHttpStatus[myType].msg);
    }
    //TODO: 公共数据解析
    
    
    log("response type = %d, data = %s\n", (int)myType, m_mapHttpStatus[myType].jsonRoot.toStyledString().c_str());

    //回调
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
