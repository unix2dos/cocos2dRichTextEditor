//
//  RichViewManager.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/10.
//

#ifndef RichViewManager_hpp
#define RichViewManager_hpp

class CRichViewManager : public cocos2d::Ref
{
public:
    CRichViewManager();
    virtual ~CRichViewManager();
    static CRichViewManager* getInstance();
    
public:
    virtual void initRichView() = 0;
    virtual void writeJournal() = 0;
    virtual void showJournal(std::string strContext) = 0;
    virtual void closeJournal(std::string strContext) = 0;
   
protected:
    void addJournal(std::string strContext);
    
private:
    static CRichViewManager* m_pInstance;
};

#endif /* RichViewManager_hpp */
