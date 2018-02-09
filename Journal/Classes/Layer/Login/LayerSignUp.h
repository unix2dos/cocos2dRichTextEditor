//
//  LayerSignUp.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/9.
//

#ifndef LayerSignUp_hpp
#define LayerSignUp_hpp

class CLayerSignUp: public Layer
{
public:
    CLayerSignUp();
    virtual ~CLayerSignUp();
    CREATE_FUNC(CLayerSignUp);
    bool init() override;
private:
    void _initUI();
    
private:
    Size m_winSize;
};

#endif /* LayerSignUp_hpp */
