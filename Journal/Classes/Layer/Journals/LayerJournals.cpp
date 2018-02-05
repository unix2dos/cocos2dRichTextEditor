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
    
    
    _initInfo();
    _initContext();
}




void CLayerJournals::_initInfo()
{
    auto bg = Sprite::create("journal_top.png");
    bg->setPosition(Vec2(m_winSize.width/2, m_winSize.height - bg->getContentSize().height/2));
    this->addChild(bg);
    
    //头像
    auto avater = Sprite::create("avatar_default.png");
    avater->setPosition(Vec2(bg->getContentSize().width/2, bg->getContentSize().height/2));
    avater->setScale(0.1f);
    bg->addChild(avater);
    
    //名字
    auto name = Label::createWithTTF("Sample Name", MY_FONT_ENGLISH, 35);
    name->setPosition(Vec2(bg->getContentSize().width/2, 50));
    name->enableBold();
    bg->addChild(name);
    
    //width适配
    auto width = m_winSize.width * 0.15f;
    width = bg->convertToNodeSpace(Vec2(width,0)).x;
    
    //写日志
    auto btnAdd = Button::create("btn_add.png");
    btnAdd->setPosition(Vec2(width, bg->getContentSize().height/2 + 100));
    btnAdd->addClickEventListener([](Ref* r){
        CRichText::getInstance()->haha();
    });
    btnAdd->setScale(0.25f);
    bg->addChild(btnAdd);
    
    //搜索不做
    auto btnSearch = Button::create("btn_search.png");
    btnSearch->setPosition(Vec2(width, bg->getContentSize().height/2));
    btnSearch->addClickEventListener([](Ref* r){
    });
    btnSearch->setScale(0.25f);
    bg->addChild(btnSearch);
    
    //弹出板子
    auto btnDrawer = Button::create("btn_drawer.png");
    btnDrawer->setPosition(Vec2(width, bg->getContentSize().height/2 - 100));
    btnDrawer->addClickEventListener([](Ref* r){
        //TODO: show
        //    弹出页面东西,要有个特效
        //    logo
        //    3个label, 权限不一样 加数据??  加黑条?
    });
    btnDrawer->setScale(0.25f);
    bg->addChild(btnDrawer);
    
    
    //滚动顶部?
}


void CLayerJournals::_initContext()
{
    //tableview
}
