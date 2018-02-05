//
//  LayerJournalEx.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/5.
//

#ifndef LayerJournalEx_hpp
#define LayerJournalEx_hpp

class CLayerJournalEx: public Layer
{
public:
    CLayerJournalEx();
    virtual ~CLayerJournalEx();
    CREATE_FUNC(CLayerJournalEx);
    bool init() override;
private:
    void _initUI();
};

#endif /* LayerJournalEx_hpp */
