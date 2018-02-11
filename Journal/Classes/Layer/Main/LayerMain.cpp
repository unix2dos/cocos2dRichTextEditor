//
//  LayerMain.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/3.
//


#include "Journal.h"
#include "Define.h"
#include "CommonUtils.h"
#include "LayerJournals.h"
#include "LayerArchive.h"
#include "LayerJournalEx.h"
#include "LayerMain.h"


#define BUTTON_HEIGHT 100


CLayerMain::CLayerMain()
:m_status(MainStatus::Journals)
{
//    NotificationManager::getInstance()->registerNotification(NOTIFY_TYPE::JOURNAL_BG, this);
}


CLayerMain::~CLayerMain()
{
//    NotificationManager::getInstance()->unregisterNotification(NOTIFY_TYPE::JOURNAL_BG, this);
}


bool CLayerMain::init()
{
    if(!Layer::init()){
        return false;
    }
    
    _initUI();
    
    return true;
}

void CLayerMain::notifyEvent(NOTIFY_TYPE type, void* pVoid)
{
//    if (type == NOTIFY_TYPE::JOURNAL_BG)
//    {
//    }
}


void CLayerMain::_initUI()
{
    m_winSize = Director::getInstance()->getWinSize();
//    auto bg = Sprite::create("bg_main.png");
//    bg->setPosition(Vec2(m_winSize.width/2, m_winSize.height/2));
//    this->addChild(bg);
    auto bg = LayerColor::create(Color4B(255, 255, 255, 255));
    this->addChild(bg);
    
    //初始化按钮
    _initButtons();
    
    //显示默认
    this->setMainStatus(m_status);
    

//    CHttpManager::getInstance()->HttpGet(eHttpType::getinfo);//TODO:111
//    CHttpManager::getInstance()->HttpGet(eHttpType::journal_list, "/public=-1");//TODO:111
}

void CLayerMain::endWithHttpData(eHttpType myType, HttpResponseInfo rep)
{
//    if (myType == eHttpType::login)
//    {
//        if (rep.status != eHttpStatus::success)
//        {
//            log("Error %s", rep.msg.c_str());
//        }
//    }
}


void CLayerMain::_initButtons()
{
    auto layerColor = LayerColor::create(Color4B(240, 240, 240, 255), m_winSize.width, MAIN_BOTTOM_HEIGHT);
    this->addChild(layerColor, 2);
    
    
    auto btnJournals = Button::create("tab_journal.png");
    btnJournals->setPosition(Vec2(m_winSize.width*.2, BUTTON_HEIGHT));
    btnJournals->addClickEventListener([&](Ref* r){
        this->setMainStatus(MainStatus::Journals);
    });
    layerColor->addChild(btnJournals);
    auto label1 = Label::createWithTTF("Journals", MY_FONT_ENGLISH, 30);
    label1->setPosition(Vec2(btnJournals->getContentSize().width/2, -30));
    label1->setTextColor(Color4B(0,0,0,255));
    label1->setName("text");
    btnJournals->addChild(label1);
    
    

    
    auto btnArchive = Button::create("tab_archive.png");
    btnArchive->setPosition(Vec2(m_winSize.width*.5, BUTTON_HEIGHT));
    btnArchive->addClickEventListener([&](Ref* r){
        this->setMainStatus(MainStatus::Archive);
    });
    layerColor->addChild(btnArchive);
    auto label2 = Label::createWithTTF("Archive", MY_FONT_ENGLISH, 30);
    label2->setPosition(Vec2(btnArchive->getContentSize().width/2, -30));
    label2->setTextColor(Color4B(0,0,0,255));
    label2->setName("text");
    btnArchive->addChild(label2);
    
    
    
    
    auto btnJournalEx = Button::create("tab_journalex.png");
    btnJournalEx->setPosition(Vec2(m_winSize.width*.8, BUTTON_HEIGHT));
    btnJournalEx->addClickEventListener([&](Ref* r){
        this->setMainStatus(MainStatus::JournalEx);
    });
    layerColor->addChild(btnJournalEx);
    auto label3 = Label::createWithTTF("JournalEx", MY_FONT_ENGLISH, 30);
    label3->setPosition(Vec2(btnJournalEx->getContentSize().width/2, -30));
    label3->setTextColor(Color4B(0,0,0,255));
    label3->setName("text");
    btnJournalEx->addChild(label3);
    
    m_vecBtns.clear();
    m_vecBtns.push_back(btnJournals);
    m_vecBtns.push_back(btnArchive);
    m_vecBtns.push_back(btnJournalEx);
}



void CLayerMain::setMainStatus(MainStatus status)
{
    m_status = status;
    
    //common ui
    for (const auto& it : m_vecBtns){
        auto label = dynamic_cast<Label*>(it->getChildByName("text"));
        label->setTextColor(Color4B(144,144,144,255));
        it->setOpacity(100);
    }
    //layers
    for (auto it : m_mapLayers)
    {
        it.second->setVisible(false);
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
    if (!m_vecBtns.empty()){
        m_vecBtns[0]->setOpacity(255);
        auto label = dynamic_cast<Label*>(m_vecBtns[0]->getChildByName("text"));
        label->setTextColor(Color4B(0,0,0,255));
    }
    
    auto it = m_mapLayers.find("Journals");
    if (it == m_mapLayers.end())
    {
        auto layer = CLayerJournals::create();
        this->addChild(layer);
        m_mapLayers["Journals"] = layer;
    }
    else
    {
        it->second->setVisible(true);
    }
}


void CLayerMain::_showArchive()
{
    if (!m_vecBtns.empty()){
        m_vecBtns[1]->setOpacity(255);
        auto label = dynamic_cast<Label*>(m_vecBtns[1]->getChildByName("text"));
        label->setTextColor(Color4B(0,0,0,255));
    }
    
    auto it = m_mapLayers.find("Archive");
    if (it == m_mapLayers.end())
    {
        auto layer = CLayerArchive::create();
        this->addChild(layer);
        m_mapLayers["Archive"] = layer;
    }
    else
    {
        it->second->setVisible(true);
    }
}


void CLayerMain::_showJournalEx()
{
    if (!m_vecBtns.empty()){
        m_vecBtns[2]->setOpacity(255);
        auto label = dynamic_cast<Label*>(m_vecBtns[2]->getChildByName("text"));
        label->setTextColor(Color4B(0,0,0,255));
    }
    
    auto it = m_mapLayers.find("JournalEx");
    if (it == m_mapLayers.end())
    {
        auto layer = CLayerJournalEx::create();
        this->addChild(layer, 1);
        m_mapLayers["JournalEx"] = layer;
    }
    else
    {
        it->second->setVisible(true);
    }
}
