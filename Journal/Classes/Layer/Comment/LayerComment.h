//
//  LayerComment.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/26.
//

#ifndef LayerComment_hpp
#define LayerComment_hpp

class CLayerComment: public Layer
, public cocos2d::extension::TableViewDataSource
, public cocos2d::extension::TableViewDelegate
{
public:
    CLayerComment();
    virtual ~CLayerComment();
    CREATE_FUNC(CLayerComment);
    bool init() override;
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view)override ;
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view)override;
    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)override;
    virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)override;
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)override;
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table) override;
public:
    void setJournalId(int journalId);
private:
    void _initUI();
    void _requestAddComment(std::string text);
private:
    Size m_winSize;
    float m_fTableViewHeight;
    cocos2d::extension::TableView* m_pTableView;
private:
    int m_iJournalId;
};

#endif /* LayerComment_hpp */
