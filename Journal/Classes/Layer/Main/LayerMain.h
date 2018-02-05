//
//  LayerMain.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/3.
//

#ifndef LayerMain_hpp
#define LayerMain_hpp
#include "ui/UIButton.h"


enum class MainStatus{
    Journals,
    Archive,
    JournalEx,
};


class CLayerMain: public cocos2d::Layer
{
public:
    CLayerMain();
    virtual ~CLayerMain();
    CREATE_FUNC(CLayerMain);
    bool init() override;
    
    
    void setMainStatus(MainStatus status);
    
private:
    void _initUI();
    void _initFunctions();
    
    
    void _showJournals();
    void _showArchive();
    void _showJournalEx();
    
private:
    MainStatus m_status;
    std::vector<cocos2d::ui::Button*> m_vecBtns;
};

#endif /* LayerMain_hpp */
