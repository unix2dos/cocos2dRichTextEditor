//
//  LayerArchive.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/5.
//

#ifndef LayerArchive_hpp
#define LayerArchive_hpp

class CLayerArchive: public Layer
{
public:
    CLayerArchive();
    virtual ~CLayerArchive();
    CREATE_FUNC(CLayerArchive);
    bool init() override;
private:
    void _initUI();
};

#endif /* LayerArchive_hpp */
