//
//  LayerJournals.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/5.
//

USING_NS_CC;
using namespace cocos2d::ui;
using namespace std;

#include "Config.h"
#include "RichText.h"
#include "ui/UIButton.h"
#include "LayerJournals.h"



CLayerJournals::CLayerJournals()
{
    
}


CLayerJournals::~CLayerJournals(){
    
}


bool CLayerJournals::init()
{
    if(!Layer::init()){
        return false;
    }
    
    _initUI();
    
    return true;
}


void CLayerJournals::_initUI()
{
    m_winSize = Director::getInstance()->getWinSize();
    
    auto btn = Button::create("add.png");
    btn->setPosition(Vec2(m_winSize.width/2, m_winSize.height/2));
    btn->addClickEventListener([](Ref* r){
        CRichText::getInstance()->haha();
    });
    this->addChild(btn);
}


void CLayerJournals::_initInfo()
{
    //本页东西
    //头像
    auto bg = Sprite::create("journal_top.png");
    bg->setPosition(Vec2(m_winSize.width/2, m_winSize.height/2));
    this->addChild(bg);
    // 名字
    
    //2个按钮  滚动顶部?
    //tableview
    
}


void CLayerJournals::_initContext()
{
    //弹出页面东西,要有个特效
    //logo
    //3个label, 权限不一样 加数据??  加黑条?
}
