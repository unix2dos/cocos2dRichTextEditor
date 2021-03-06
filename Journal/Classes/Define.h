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

#define MY_FONT_ENGLISH "arial.ttf" //英文字体
#define MY_FONT_CHINESE "chinese.ttf"//中文字体

#define MY_DEBUG 1//测试阶段,发布版本修改成0


////////HTTP////////
//#define SERVER_ADDRESS "http://127.0.0.1:8080" //服务器地址
#define SERVER_ADDRESS "http://140.82.56.114:8080" //线上地址

enum class eHttpType
{
    none = 0,
    getinfo,     //获取用户信息
    signup,      //注册,ok
    login,       //登录,ok
    journal_list,//日志信息
    journal_add, //添加日志,ok
    journal_update,//修改日志,ok
    journal_delete,//删除日志
    journal_recommend,//推荐日志,ok
    comment_list,//留言信息,ok
    comment_add,//留言增加,ok
    comment_update,//留言更新
    comment_delete,//留言删除
    like_add,//喜欢添加
    like_delete,//喜欢删除
    archive_get,//喜欢的
};
static std::map<eHttpType, std::string> HTTPURLMAP
{
    {eHttpType::getinfo,            SERVER_ADDRESS"/getinfo"},
    {eHttpType::signup,             SERVER_ADDRESS"/signup"},
    {eHttpType::login,              SERVER_ADDRESS"/login"},
    {eHttpType::journal_list,       SERVER_ADDRESS"/journal/list"},
    {eHttpType::journal_add,        SERVER_ADDRESS"/journal/add"},
    {eHttpType::journal_update,     SERVER_ADDRESS"/journal/update"},
    {eHttpType::journal_delete,     SERVER_ADDRESS"/journal/delete"},
    
    {eHttpType::journal_recommend,  SERVER_ADDRESS"/journal/recommend"},
    {eHttpType::comment_list,       SERVER_ADDRESS"/comment/list"},
    {eHttpType::comment_add,        SERVER_ADDRESS"/comment/add"},
    {eHttpType::comment_update,     SERVER_ADDRESS"/comment/update"},
    {eHttpType::comment_delete,     SERVER_ADDRESS"/comment/delete"},
    {eHttpType::like_add,           SERVER_ADDRESS"/like/add"},
    {eHttpType::like_delete,        SERVER_ADDRESS"/like/delete"},
    {eHttpType::archive_get,        SERVER_ADDRESS"/archive/get"},
};



////////NOTIFY_TYPE////////
enum class NOTIFY_TYPE
{
    journal_data_change,//日志数据变化
};


////////ZORDER////////
#define MYDFE_ZORDER_MSG 1000   //弹窗消息




////////XML SAVE////////
#define DATA_SAVE_COOKIE "DATA_SAVE_COOKIE"


////////MOVE DIR////////
enum class MOVE_DIR
{
    NONE,
    LEFT,
    RIGHT
};


#endif /* Define_h */
