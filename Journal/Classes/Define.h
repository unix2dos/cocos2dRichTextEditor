//
//  Define.h
//  Journal
//
//  Created by liuwei on 2018/2/7.
//

#ifndef Define_h
#define Define_h

#define MY_DESIGNSIZE_W  1000.0f //设计分辨率宽
#define MY_DESIGNSIZE_H  1334.0f //设计分辨率高

#define MY_FONT_ENGLISH "arial.ttf" //字体


////////HTTP////////
#define SERVER_ADDRESS "http://journalex.us:5000" //服务器地址
enum class eHttpType
{
    none = 0,
    getinfo,     //获取用户信息
    signup,      //注册
    login,       //登录
    journal_list,//日志信息
    journal_add, //添加日志
};
static std::map<eHttpType, std::string> HTTPURLMAP
{
    {eHttpType::getinfo,        SERVER_ADDRESS"/getinfo"},
    {eHttpType::signup,         SERVER_ADDRESS"/signup"},
    {eHttpType::login,          SERVER_ADDRESS"/login"},
    {eHttpType::journal_list,   SERVER_ADDRESS"/journal/list"},
    {eHttpType::journal_add,    SERVER_ADDRESS"/journal/add"}
};


///NOTIFY_TYPE
enum class NOTIFY_TYPE
{
    journal_data_change,//日志数据变化
};


////////ZORDER////////
#define MYDFE_ZORDER_MSG 1000   //弹窗消息



#endif /* Define_h */
