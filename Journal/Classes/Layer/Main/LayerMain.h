//
//  LayerMain.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/3.
//

#ifndef LayerMain_hpp
#define LayerMain_hpp

#define MAIN_BOTTOM_HEIGHT 150 //底部高度

enum class MainStatus{
    Journals,
    Archive,
    JournalEx,
};


class CLayerMain: public Layer
{
public:
    CLayerMain();
    virtual ~CLayerMain();
    CREATE_FUNC(CLayerMain);
    bool init() override;
    
    
    void setMainStatus(MainStatus status);
    
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
};

#endif /* LayerMain_hpp */
