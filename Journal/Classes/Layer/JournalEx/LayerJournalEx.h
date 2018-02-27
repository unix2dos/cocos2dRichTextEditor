//
//  LayerJournalEx.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/5.
//

#ifndef LayerJournalEx_hpp
#define LayerJournalEx_hpp

#include "HttpManager.h"

class CLayerJournalEx: public Layer
, public cocos2d::extension::TableViewDataSource
, public cocos2d::extension::TableViewDelegate
, public CDataHttpDelegate
{
public:
    CLayerJournalEx();
    virtual ~CLayerJournalEx();
    CREATE_FUNC(CLayerJournalEx);
    bool init() override;
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view)override ;
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view)override;
    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)override;
    virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)override;
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)override;
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table) override;
    virtual void endWithHttpData(eHttpType myType, HttpResponseInfo rep) override;
public:
    void updateUI();
private:
    void _initUI();
private:
    Size m_winSize;
    float m_fTableViewHeight;
    cocos2d::extension::TableView* m_pTableView;
};

#endif /* LayerJournalEx_hpp */
