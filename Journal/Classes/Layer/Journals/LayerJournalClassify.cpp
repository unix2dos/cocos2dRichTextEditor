//
//  LayerJournalCassify.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/6.
//

#include "Journal.h"
#include "Define.h"
#include "LayerJournals.h"
#include "LayerJournalClassify.h"


CLayerJournalClassify::CLayerJournalClassify()
:m_pSelect(nullptr)
{
    
}


CLayerJournalClassify::~CLayerJournalClassify(){
    
}

void CLayerJournalClassify::onEnter()
{
    Layer::onEnter();
    auto classify = this->getChildByName("classify");
    if (classify)
    {
        auto pos = classify->getPosition();
        classify->setPosition(Vec2(pos.x - m_winSize.width*.4, pos.y));
        classify->runAction(MoveTo::create(0.2f, pos));
    }
}

void CLayerJournalClassify::onExit()
{

    Layer::onExit();
}

bool CLayerJournalClassify::init()
{
    if(!Layer::init()){
        return false;
    }
    
    _initUI();
    
    return true;
}


void CLayerJournalClassify::_initUI()
{
    m_winSize = Director::getInstance()->getWinSize();
    
    //黑色layerColor
    auto mark = LayerColor::create(Color4B(0, 0, 0, 180));
    this->addChild(mark);

    
    //白色左边
    auto classify = LayerColor::create(Color4B(255, 255, 255, 255), m_winSize.width*.4, m_winSize.height);
    classify->setName("classify");
    this->addChild(classify);
    
    //logo
    auto logo = Sprite::create("logo.png");
    logo->setPosition(Vec2(classify->getContentSize().width*.5f, classify->getContentSize().height*.9));
    classify->addChild(logo);
    
    
    auto draw = DrawNode::create();
    draw->drawLine(Point(0, classify->getContentSize().height*.8), Point(classify->getContentSize().width, classify->getContentSize().height*.8), Color4F::GRAY);
    classify->addChild(draw);
    
    m_pSelect = Sprite::create();
    m_pSelect->setTextureRect(Rect(0, 0, classify->getContentSize().width, 100));
    m_pSelect->setColor(Color3B(0, 0, 0));
    m_pSelect->setAnchorPoint(Vec2(.5,1));
    m_pSelect->setPosition(Vec2(classify->getContentSize().width*.5f, classify->getContentSize().height*.8-200));
    classify->addChild(m_pSelect);
    m_pSelect->setVisible(false);
    
    
    
    auto all = Sprite::create();
    all->setTextureRect(Rect(0, 0, classify->getContentSize().width, 100));
    all->setColor(Color3B(255, 0, 0));
    all->setOpacity(0);
    all->setAnchorPoint(Vec2(.5, 1));
    all->setPosition(Vec2(classify->getContentSize().width*.5f, classify->getContentSize().height*.8));
    classify->addChild(all);
    auto labelall = Label::createWithTTF("All Journals", MY_FONT_CHINESE, 30);
    labelall->setPosition(Vec2(20, all->getContentSize().height/2));
    labelall->setTextColor(Color4B(0,0,0,255));
    labelall->setAnchorPoint(Vec2(0, 0.5));
    labelall->setName("text");
    all->addChild(labelall);
    
    
    auto pub = Sprite::create();
    pub->setTextureRect(Rect(0, 0, classify->getContentSize().width, 100));
    pub->setColor(Color3B(255, 0, 0));
    pub->setOpacity(0);
    pub->setAnchorPoint(Vec2(.5,1));
    pub->setPosition(Vec2(classify->getContentSize().width*.5f, classify->getContentSize().height*.8-100));
    classify->addChild(pub);
    auto labelpub = Label::createWithTTF("Public Journals", MY_FONT_CHINESE, 30);
    labelpub->setPosition(Vec2(20, all->getContentSize().height/2));
    labelpub->setTextColor(Color4B(0,0,0,255));
    labelpub->setAnchorPoint(Vec2(0, 0.5));
    labelpub->setName("text");
    pub->addChild(labelpub);
    
    
    auto pri = Sprite::create();
    pri->setTextureRect(Rect(0, 0, classify->getContentSize().width, 100));
    pri->setColor(Color3B(255, 0, 0));
    pri->setOpacity(0);
    pri->setAnchorPoint(Vec2(.5,1));
    pri->setPosition(Vec2(classify->getContentSize().width*.5f, classify->getContentSize().height*.8-200));
    classify->addChild(pri);
    auto labelpri = Label::createWithTTF("Private Journals", MY_FONT_CHINESE, 30);
    labelpri->setPosition(Vec2(20, all->getContentSize().height/2));
    labelpri->setTextColor(Color4B(0,0,0,255));
    labelpri->setAnchorPoint(Vec2(0, 0.5));
    labelpri->setName("text");
    pri->addChild(labelpri);

    
    m_pLabels.clear();
    m_pLabels.push_back(all);
    m_pLabels.push_back(pub);
    m_pLabels.push_back(pri);
    

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(CLayerJournalClassify::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(CLayerJournalClassify::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void CLayerJournalClassify::_closeUI()
{
    auto call = CallFunc::create([&](){
        this->removeFromParent();
    });
    
    auto classify = this->getChildByName("classify");
    if (classify)
    {
        auto pos = classify->getPosition();
        classify->runAction(Sequence::create(
                                             DelayTime::create(0.3f),
                                             MoveTo::create(0.2f, Vec2(pos.x - m_winSize.width*.4, pos.y)),
                                             call,
                                             nullptr)
                            );
    }
    else
    {
        this->runAction(call);
    }
}

void CLayerJournalClassify::_onClickLabel(int index)
{
    for (const auto& it : m_pLabels)
    {
        auto label = dynamic_cast<Label*>(it->getChildByName("text"));
        if (label)
        {
            label->setTextColor(Color4B(0,0,0,255));
        }
    }
    
    if (m_pSelect)
    {
        m_pSelect->setVisible(true);
        m_pSelect->setPosition(m_pLabels[index]->getPosition());
    }
    
    auto label = dynamic_cast<Label*>(m_pLabels[index]->getChildByName("text"));
    if (label)
    {
        label->setTextColor(Color4B(255,255,255,255));
    }
    
    auto LayerJournals = dynamic_cast<CLayerJournals*>(this->getParent());
    if (LayerJournals)
    {
        ShowType type = ShowType::All;
        if (index == 0){type = ShowType::All;}
        else if (index == 1){type = ShowType::Public;}
        else if(index == 2){type = ShowType::Private;}
        LayerJournals->setShowType(type);
    }
    
    this->_closeUI();
}


bool CLayerJournalClassify::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    auto classify = this->getChildByName("classify");
    if (classify){
        if (classify->getBoundingBox().containsPoint(classify->getParent()->convertTouchToNodeSpace(touch))){
            for (int i = 0; i < m_pLabels.size(); ++i)
            {
                if (m_pLabels[i]->getBoundingBox().containsPoint(classify->getParent()->convertTouchToNodeSpace(touch))){
                    _onClickLabel(i);
                    break;
                }
            }
        }
        else
        {
            this->_closeUI();
        }
    }
    
    return true;
}

void CLayerJournalClassify::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
}
