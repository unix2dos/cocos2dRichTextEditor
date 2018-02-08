//
//  LayerMain.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/3.
//

#ifndef LayerMain_hpp
#define LayerMain_hpp

#include "HttpManager.h"
#include "NotificationManager.h"

#define MAIN_BOTTOM_HEIGHT 150 //底部高度

enum class MainStatus{
    Journals,
    Archive,
    JournalEx,
};


class CLayerMain: public Layer
, public CDataHttpDelegate
, public CNotificationDelegate
{
public:
    CLayerMain();
    virtual ~CLayerMain();
    CREATE_FUNC(CLayerMain);
    bool init() override;
    
    
    void setMainStatus(MainStatus status);
    virtual void endWithHttpData(eHttpType myType, HttpResponseInfo rep) override;
    virtual void notifyEvent(NOTIFY_TYPE type, void* pVoid = nullptr) override;
private:
    void _initUI();
    void _initButtons();
    
    
    void _showJournals();
    void _showArchive();
    void _showJournalEx();
    
private:
    Size m_winSize;
    MainStatus m_status;
    std::vector<cocos2d::ui::Button*> m_vecBtns;
    std::map<std::string, cocos2d::Layer*> m_mapLayers;
};

#endif /* LayerMain_hpp */
