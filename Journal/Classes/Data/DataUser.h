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
    std::string username;
};


class CDataUser
{
public:
    CDataUser();
    ~CDataUser();
public:
    const User_Info& getUserInfo();
private:
    User_Info m_userInfo;
};

#endif /* DataUser_hpp */
