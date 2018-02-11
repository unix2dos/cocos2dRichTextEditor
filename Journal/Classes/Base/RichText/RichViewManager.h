//
//  RichViewManager.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/10.
//

#ifndef RichViewManager_hpp
#define RichViewManager_hpp
#include "DataJournal.h"

enum class RichViewType
{
    none,
    write,
    show_self,
    show_others,
};

//不能存放平台有关的数据
class CRichViewManager : public cocos2d::Ref
{
    static CRichViewManager* m_pInstance;
public:
    CRichViewManager();
    virtual ~CRichViewManager();
    static CRichViewManager* getInstance();
    
public:
    virtual void initRichView();
    virtual void newJournal();
    virtual void showJournal(const Journal_Info& info, bool myself);
    virtual void closeJournal();
    
    Journal_Info& getJournal();
    RichViewType getRichViewType();
    
    void requestAddJournal();
    void requestUpdateJournal();
    
private:
    Journal_Info m_journalInfo;
    RichViewType m_richviewType;
};

#endif /* RichViewManager_hpp */
