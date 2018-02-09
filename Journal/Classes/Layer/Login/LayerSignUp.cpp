//
//  LayerSignUp.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/9.
//

#include "Journal.h"
#include "LayerSignUp.h"


CLayerSignUp::CLayerSignUp(){
    
}


CLayerSignUp::~CLayerSignUp(){
}


bool CLayerSignUp::init()
{
    if(!Layer::init()){
        return false;
    }
    
    _initUI();
    
    return true;
}


void CLayerSignUp::_initUI()
{
    m_winSize = Director::getInstance()->getVisibleSize();
}
