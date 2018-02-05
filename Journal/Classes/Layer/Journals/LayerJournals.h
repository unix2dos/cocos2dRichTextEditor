//
//  LayerJournals.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/5.
//

#ifndef LayerJournals_hpp
#define LayerJournals_hpp

class CLayerJournals: public cocos2d::Layer
{
public:
    CLayerJournals();
    virtual ~CLayerJournals();
    CREATE_FUNC(CLayerJournals);
    bool init() override;    
private:
    void _initUI();
};

#endif /* LayerJournals_hpp */
