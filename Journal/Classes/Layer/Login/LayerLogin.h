//
//  LayerLogin.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/9.
//

#ifndef LayerLogin_hpp
#define LayerLogin_hpp

class CLayerLogin: public Layer
{
public:
    CLayerLogin();
    virtual ~CLayerLogin();
    CREATE_FUNC(CLayerLogin);
    bool init() override;
private:
    void _initUI();
    
private:
    Size m_winSize;
};

#endif /* LayerLogin_hpp */
