//
//  SceneManager.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/3.
//

#ifndef SceneManager_hpp
#define SceneManager_hpp



enum class eSceneType
{
    none = 0,
    launch, //开机页面
    login, //登录注册页面
    main, //主界面
};

class CSceneBase;
class CSceneManager : public Ref
{
public:
    static CSceneManager* getInstance();
    static void destroyInstance();
    
public:
    CSceneManager();
    ~CSceneManager();
    void init();
    void free();

public:
    static CSceneBase* jumpToScene(eSceneType eType);
    static CSceneBase* getRunSCene();
    
public:
    eSceneType getSceneLastType();
    void setSceneLastType(eSceneType type);
    
    eSceneType getSceneCurrType();
    void setSceneCurrType(eSceneType type);
    
    CSceneBase* getCurrScene();
    void setCurrScene(CSceneBase* p);
    
private:
    eSceneType m_eLastType;
    eSceneType m_eCurrType;
    CSceneBase* m_currScene;

};

#endif /* SceneManager_hpp */
