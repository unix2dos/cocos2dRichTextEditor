//
//  HttpManager.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/7.
//

#ifndef HttpManager_hpp
#define HttpManager_hpp


//http状态
enum class eHttpStatus
{
    none = 0,
    sending,//发送中
    sendErr,//发送错误
    serverErr,//服务器错误
    logicErr,//逻辑错误
    success,//成功
};


//响应数据
struct HttpResponseInfo
{
    eHttpStatus status;//状态
    std::string msg;//消息
    Json::Value jsonRoot;//json数据
    
    HttpResponseInfo()
    {
        status = eHttpStatus::none;
        msg = "NULL";
        jsonRoot = Json::nullValue;
    }
};


//消息回调继承这个
enum class eHttpType;
class CDataHttpDelegate
{
public:
    CDataHttpDelegate();
    virtual ~CDataHttpDelegate();
    virtual void endWithHttpData(eHttpType myType, HttpResponseInfo rep) = 0;
};


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
    bool HttpGet(eHttpType myType, std::string data = "");
    bool HttpPost(eHttpType myType, std::string data);
    bool HttpSendRequest(HttpRequest::Type type, eHttpType myType, std::string data);

private:
    void _onHttpRequestCompleted(HttpClient *sender, HttpResponse *response);
    std::vector<std::string> _getCommonHeaders();
    void _parseCookie(const std::vector<char>* headData);
    std::string _getCookie();
private:
    std::map<eHttpType, HttpResponseInfo> m_mapHttpStatus;
    std::set<CDataHttpDelegate*> m_setDataRegister;
    std::mutex m_mutexCookie;
};


#endif /* HttpManager_hpp */
