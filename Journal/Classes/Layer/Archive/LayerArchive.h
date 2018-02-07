//
//  LayerArchive.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/5.
//

#ifndef LayerArchive_hpp
#define LayerArchive_hpp

class CLayerArchive: public Layer
, public cocos2d::extension::TableViewDataSource
, public cocos2d::extension::TableViewDelegate
{
public:
    CLayerArchive();
    virtual ~CLayerArchive();
    CREATE_FUNC(CLayerArchive);
    bool init() override;
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view)override ;
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view)override;
    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)override;
    virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)override;
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)override;
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table) override;
private:
    void _initUI();
private:
    Size m_winSize;
    float m_fTableViewHeight;
    cocos2d::extension::TableView* m_pTableView;
};

#endif /* LayerArchive_hpp */
