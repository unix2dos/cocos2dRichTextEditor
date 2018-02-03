//
//  LayerMain.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/3.
//

#ifndef LayerMain_hpp
#define LayerMain_hpp

class CLayerMain: public cocos2d::Layer
{
public:
    CLayerMain();
    virtual ~CLayerMain();
    CREATE_FUNC(CLayerMain);
    bool init() override;
private:
    void _initUI();
private:

};

#endif /* LayerMain_hpp */
