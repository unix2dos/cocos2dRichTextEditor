//
//  HttpManager.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/7.
//

#include "Journal.h"
#include "CommonUtils.h"
#include "Define.h"
#include "DataManager.h"
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


bool CHttpManager::HttpPost(eHttpType myType, std::string data)
{
    return HttpSendRequest(HttpRequest::Type::POST, myType, data);
}
bool CHttpManager::HttpGet(eHttpType myType, std::string data)
{
    return HttpSendRequest(HttpRequest::Type::GET, myType, data);
}

bool CHttpManager::HttpSendRequest(HttpRequest::Type type, eHttpType myType, std::string data)
{
    //status
    if (m_mapHttpStatus[myType].status == eHttpStatus::sending)
    {
        return false;
    }
    m_mapHttpStatus[myType].status = eHttpStatus::sending;
    
    //url
    std::string url = HTTPURLMAP[myType];
    if (type == HttpRequest::Type::GET && data.size() > 0)
    {
        url += data;
        data = "";
    }
    
    //request
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
    
    if (MY_DEBUG)
    {
        std::string strHead = "";
        for (auto&it : headers) {
            strHead += "\n" + it;
        }
        std::string strUrl = url.substr(strlen(SERVER_ADDRESS));
        log("--------------------------------\nrequest type= %s data= %s\nheader= %s\n--------------------------------\n", strUrl.c_str(), data.c_str(), strHead.c_str());
    }

    return true;

}

void CHttpManager::_onHttpRequestCompleted(HttpClient *sender, HttpResponse *response)
{
    if (!response)
    {
        return;
    }

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
    

    if (MY_DEBUG)
    {
        std::vector<char> *buffer = response->getResponseHeader();
        std::string strHead = "";
        strHead.assign(buffer->begin(), buffer->end());
        std::string url = response->getHttpRequest()->getUrl();
        url = url.substr(strlen(SERVER_ADDRESS));
        log("++++++++++++++++++++++++++++++++\nresponse type= %s code= %d data= %shead= %s\n++++++++++++++++++++++++++++++++\n", url.c_str(), (int)response->getResponseCode(), m_mapHttpStatus[myType].jsonRoot.toStyledString().c_str(), strHead.c_str());
    }

    //解析Cookie
    //    _parseCookie(response->getResponseHeader());//TODO: 验证不加cookie的形式
    
    //数据解析,错误统一处理
    CDataManager::getInstance()->parseServeData(myType, m_mapHttpStatus[myType]);

    //回调通知,需要处理错误
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
    std::string cookie = _getCookie();
    if (cookie != "")
    {
        cookie = "Cookie: " + cookie;
        commonHeaders.push_back(cookie);
    }
    return commonHeaders;
}


void CHttpManager::_parseCookie(const std::vector<char>* headData)
{
    std::lock_guard<std::mutex> lock(m_mutexCookie);
    std::string strHead = "";
    strHead.assign(headData->begin(), headData->end());

    std::string strFind = "Set-Cookie: ";
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    strFind = "Set-Cookie:";
#endif
    auto pos1 = strHead.find(strFind);
    auto pos2 = strHead.find("; Path=/");
    if (pos1 == std::string::npos || pos2 == std::string::npos)
    {
        return;
    }
    
    std::string strCookie = strHead.substr(pos1+strFind.length(), pos2 - pos1 - strFind.length());
    UserDefault::getInstance()->setStringForKey(DATA_SAVE_COOKIE, strCookie);
    log("\nparseCookie= %s\n\n", strCookie.c_str());
}


std::string CHttpManager::_getCookie()
{
    std::lock_guard<std::mutex> lock(m_mutexCookie);
    
    std::string strCookie = UserDefault::getInstance()->getStringForKey(DATA_SAVE_COOKIE, "");
    return strCookie;
}
