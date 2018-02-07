//
//  HttpManager.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/7.
//

#ifndef HttpManager_hpp
#define HttpManager_hpp

#include "HttpDefine.h"

class CHttpManager : public Ref
{
public:
    static CHttpManager* getInstance();
    static void destroyInstance();
    
public:
    CHttpManager();
    ~CHttpManager();
    void init();
    void free();
    void registerCallBack(CDataHttpDelegate* p);
    void unregisterCallBack(CDataHttpDelegate* p);
    
public:
    bool HttpPost(string url, eHttpType myType, std::string data);
    bool HttpGet(string url, eHttpType myType, std::string data);
    bool HttpSendRequest(HttpRequest::Type type, string url, eHttpType myType, std::string data);
    
private:
    void _onHttpRequestCompleted(HttpClient *sender, HttpResponse *response);
    std::vector<std::string> _getCommonHeaders();
    void checkErrorCode(eHttpType e,std::string nCode);
    
private:
    std::map<eHttpType, HttpStatusInfo> m_mapHttpStatus;
    std::set<CDataHttpDelegate*> m_setDataRegister;
};


#endif /* HttpManager_hpp */
