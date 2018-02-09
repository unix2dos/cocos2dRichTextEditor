//
//  LayerLogin.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/9.
//

#include "Journal.h"
#include "LayerLogin.h"


CLayerLogin::CLayerLogin(){
    
}


CLayerLogin::~CLayerLogin(){
}


bool CLayerLogin::init()
{
    if(!Layer::init()){
        return false;
    }
    
    _initUI();
    
    return true;
}


void CLayerLogin::_initUI()
{
    m_winSize = Director::getInstance()->getVisibleSize();
}
