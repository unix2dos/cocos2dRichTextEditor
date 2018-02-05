//
//  LayerJournals.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/5.
//

#ifndef LayerJournals_hpp
#define LayerJournals_hpp

class CLayerJournals: public Layer
{
public:
    CLayerJournals();
    virtual ~CLayerJournals();
    CREATE_FUNC(CLayerJournals);
    bool init() override;    
private:
    void _initUI();
    
    void _initInfo();
    void _initContext();
    
private:
    Size m_winSize;
};

#endif /* LayerJournals_hpp */
