//
//  SceneMain.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/3.
//

#ifndef SceneMain_hpp
#define SceneMain_hpp
#include "SceneBase.h"

class CSceneMain: public CSceneBase
{
public:
    CSceneMain();
    virtual ~CSceneMain();
    CREATE_FUNC(CSceneMain);
    bool init() override;
};
#endif /* SceneMain_hpp */
