//
//  SceneLogin.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/9.
//

#ifndef SceneLogin_hpp
#define SceneLogin_hpp

class CSceneLogin: public CSceneBase
{
public:
    CSceneLogin();
    virtual ~CSceneLogin();
    CREATE_FUNC(CSceneLogin);
    bool init() override;
};

#endif /* SceneLogin_hpp */
