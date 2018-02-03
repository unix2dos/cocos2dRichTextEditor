//
//  SceneBase.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/3.
//

#ifndef SceneBase_hpp
#define SceneBase_hpp

class CSceneBase: public cocos2d::Scene
{
public:
    CSceneBase();
    virtual ~CSceneBase();
    virtual bool init() override;
};

#endif /* SceneBase_hpp */
