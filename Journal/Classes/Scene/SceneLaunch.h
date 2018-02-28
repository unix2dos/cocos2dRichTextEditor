//
//  SceneLaunch.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/3.
//

#ifndef SceneLaunch_hpp
#define SceneLaunch_hpp


#include "HttpManager.h"

class CSceneLaunch: public CSceneBase
, public CDataHttpDelegate
{
public:
    CSceneLaunch();
    virtual ~CSceneLaunch();
    CREATE_FUNC(CSceneLaunch);
    bool init() override;
    virtual void endWithHttpData(eHttpType myType, HttpResponseInfo rep) override;
};

#endif /* SceneLaunch_hpp */
