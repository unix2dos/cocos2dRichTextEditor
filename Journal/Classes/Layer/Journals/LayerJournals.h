//
//  LayerJournals.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/5.
//

#ifndef LayerJournals_hpp
#define LayerJournals_hpp

enum class ShowType
{
    None,
    All,
    Public,
    Private
};


#include "NotificationManager.h"
#include "HttpManager.h"
#include "DataJournal.h"


class CLayerJournals: public Layer
, public cocos2d::extension::TableViewDataSource
, public cocos2d::extension::TableViewDelegate
, public CNotificationDelegate
, public CDataHttpDelegate
{
public:
    CLayerJournals();
    virtual ~CLayerJournals();
    CREATE_FUNC(CLayerJournals);
    bool init() override;
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view)override ;
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view)override;
    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)override;
    virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)override;
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)override;
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table) override;
    virtual void notifyEvent(NOTIFY_TYPE type, void* pVoid = nullptr) override;
    virtual void endWithHttpData(eHttpType myType, HttpResponseInfo rep) override;
public:
    void setShowType(ShowType type);
private:
    void _initUI();
    void _updateData();
private:
    Size m_winSize;
    float m_fTableViewHeight;
    cocos2d::extension::TableView* m_pTableView;
    
private:
    ShowType m_showType;
    std::vector<Journal_Info> m_showJournals;
};


#endif /* LayerJournals_hpp */
