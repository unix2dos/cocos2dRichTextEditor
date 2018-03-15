//
//  DataUser.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/6.
//

#ifndef DataUser_hpp
#define DataUser_hpp


struct User_Info
{
    std::string email;
    std::string avatar;
    std::string alias;
    int userid;
    
    User_Info()
    {
        email = "";
        avatar = "";
        alias = "";
        userid = -1;
    }
};

class HttpResponseInfo;
class CDataUser
{
public:
    CDataUser();
    ~CDataUser();
public:
    void parseServeData(HttpResponseInfo rep);
    const User_Info& getUserInfo();
public:
    void requestSignUp(std::string strEmail, std::string strPass, std::string strAlias);
    void requestLogin(std::string strEmail, std::string strPass);
    
private:
    User_Info m_userInfo;
};

#endif /* DataUser_hpp */
