//
//  LayerMain.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/3.
//


USING_NS_CC;
using namespace cocos2d::ui;
using namespace std;


#include "Config.h"
#include "LayerJournals.h"
#include "LayerArchive.h"
#include "LayerJournalEx.h"
#include "LayerMain.h"

#define FUNCTIONS_HEIGHT 100


CLayerMain::CLayerMain()
:m_status(MainStatus::Journals)
{
    
}


CLayerMain::~CLayerMain(){
    
}


bool CLayerMain::init()
{
    if(!Layer::init()){
        return false;
    }
    
    _initUI();
    
    return true;
}


void CLayerMain::_initUI()
{
    Size size = Director::getInstance()->getWinSize();
    auto bg = Sprite::create("bg_main.png");
    bg->setPosition(Vec2(size.width/2, size.height/2));
    this->addChild(bg);
    
    //初始化功能
    _initFunctions();
}



void CLayerMain::_initFunctions()
{
    Size size = Director::getInstance()->getWinSize();
    
    auto layerColor = LayerColor::create(Color4B(220, 220, 220, 255), size.width, 150);
    this->addChild(layerColor, 2);
    
    
    auto btnJournals = Button::create("tab-journal.png");
    btnJournals->setScale(.5f);
    btnJournals->setPosition(Vec2(size.width*.25, FUNCTIONS_HEIGHT));
    btnJournals->addClickEventListener([&](Ref* r){
        this->setMainStatus(MainStatus::Journals);
    });
    layerColor->addChild(btnJournals);
    auto label1 = Label::createWithTTF("Journals", MY_FONT_ENGLISH, 50);
    label1->setPosition(Vec2(btnJournals->getContentSize().width/2, -50));
    label1->setTextColor(Color4B(0,0,0,255));
    label1->setName("text");
    btnJournals->addChild(label1);
    


    
    
    
    auto btnArchive = Button::create("tab-profile.png");
    btnArchive->setScale(.5f);
    btnArchive->setPosition(Vec2(size.width*.5, FUNCTIONS_HEIGHT));
    btnArchive->addClickEventListener([&](Ref* r){
        this->setMainStatus(MainStatus::Archive);
    });
    layerColor->addChild(btnArchive);
    auto label2 = Label::createWithTTF("Archive", MY_FONT_ENGLISH, 50);
    label2->setPosition(Vec2(btnArchive->getContentSize().width/2, -50));
    label2->setTextColor(Color4B(0,0,0,255));
    label2->setName("text");
    btnArchive->addChild(label2);
    
    
    
    
    auto btnJournalEx = Button::create("tab-journalex.png");
    btnJournalEx->setScale(.5f);
    btnJournalEx->setPosition(Vec2(size.width*.75, FUNCTIONS_HEIGHT));
    btnJournalEx->addClickEventListener([&](Ref* r){
        this->setMainStatus(MainStatus::JournalEx);
    });
    layerColor->addChild(btnJournalEx);
    auto label3 = Label::createWithTTF("JournalEx", MY_FONT_ENGLISH, 50);
    label3->setPosition(Vec2(btnJournalEx->getContentSize().width/2, -50));
    label3->setTextColor(Color4B(0,0,0,255));
    label3->setName("text");
    btnJournalEx->addChild(label3);
    
    m_vecBtns.clear();
    m_vecBtns.push_back(btnJournals);
    m_vecBtns.push_back(btnArchive);
    m_vecBtns.push_back(btnJournalEx);
    
    this->setMainStatus(m_status);
}



void CLayerMain::setMainStatus(MainStatus status)
{
    m_status = status;
    
    //common ui
    for (const auto& it : m_vecBtns){
        auto label = dynamic_cast<Label*>(it->getChildByName("text"));
        label->setTextColor(Color4B(144,144,144,255));
    }
    auto layer = this->getChildByTag(100);
    if (layer)
    {
        layer->removeFromParent();
    }
    
    //ui
    switch (status) {
        case MainStatus::Journals:
            _showJournals();
            break;
        case MainStatus::Archive:
            _showArchive();
            break;
        case MainStatus::JournalEx:
            _showJournalEx();
            break;
        default:
            break;
    }
}


void CLayerMain::_showJournals()
{
    auto label = dynamic_cast<Label*>(m_vecBtns[0]->getChildByName("text"));
    label->setTextColor(Color4B(0,0,0,255));
    
    auto layer = CLayerJournals::create();
    layer->setTag(100);
    this->addChild(layer);
}


void CLayerMain::_showArchive()
{
    auto label = dynamic_cast<Label*>(m_vecBtns[1]->getChildByName("text"));
    label->setTextColor(Color4B(0,0,0,255));
    
    auto layer = CLayerArchive::create();
    layer->setTag(100);
    this->addChild(layer);
}


void CLayerMain::_showJournalEx()
{
    auto label = dynamic_cast<Label*>(m_vecBtns[2]->getChildByName("text"));
    label->setTextColor(Color4B(0,0,0,255));
    
    auto layer = CLayerJournalEx::create();
    layer->setTag(100);
    this->addChild(layer, 1);
}
