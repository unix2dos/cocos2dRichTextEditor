//
//  SceneLaunch.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/3.
//

#ifndef SceneLaunch_hpp
#define SceneLaunch_hpp


class CSceneLaunch: public CSceneBase
{
public:
    CSceneLaunch();
    virtual ~CSceneLaunch();
    CREATE_FUNC(CSceneLaunch);
    bool init() override;
};

#endif /* SceneLaunch_hpp */
