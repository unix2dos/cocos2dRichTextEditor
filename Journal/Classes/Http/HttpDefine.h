//
//  HttpDefine.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/7.
//

#ifndef HttpDefine_hpp
#define HttpDefine_hpp


enum class eHttpType
{
    login = 1,//登录
};


enum class eHttpStatus
{
    None,
    Send,//发送中
    Serr,//发送错误
    Rok,//返回成功
    Rerr,//返回错误
};


struct HttpStatusInfo
{
    eHttpStatus status;
    std::string msg;
    HttpStatusInfo():status(eHttpStatus::None),msg("NULL")
    {}
};

//消息回调继承这个
class CDataHttpDelegate
{
public:
    CDataHttpDelegate();
    virtual ~CDataHttpDelegate();
    virtual void endWithHttpData(eHttpType myType, HttpStatusInfo info) = 0;
};


#endif /* HttpDefine_hpp */
