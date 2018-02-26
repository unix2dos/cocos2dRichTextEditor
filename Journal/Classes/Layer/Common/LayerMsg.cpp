#include "Journal.h"
#include "Define.h"
#include "LayerMsg.h"

CLayerMsg::CLayerMsg()
{
}

CLayerMsg::~CLayerMsg()
{
}


CLayerMsg* CLayerMsg::create(std::string msg)
{
    auto r = new CLayerMsg();
    r ->autorelease();
    r->init(msg);
    return  r;
}

bool CLayerMsg::init(std::string msg)
{
    if (!Layer::init())
    {
        return false;
    }
    
    ui::Scale9Sprite* pWordBg = ui::Scale9Sprite::create("ui_txt_back.png");
    this->addChild(pWordBg);
    
    auto label = Label::create();
    label->setHorizontalAlignment(TextHAlignment::CENTER);
    label->setVerticalAlignment(TextVAlignment::TOP);
    label->setOverflow(Label::Overflow::RESIZE_HEIGHT);
    
    TTFConfig ttfConfig(MY_FONT_CHINESE, 30, GlyphCollection::DYNAMIC);
    label->setTTFConfig(ttfConfig);
    label->setTextColor(Color4B(98, 36, 4, 255));
    label->setDimensions(1000, 500);
    label->setString(msg);
    auto size = label->getContentSize();
    pWordBg->setContentSize(size + Size(40,40));
    this->addChild(label);
    label->setPosition(Vec2(size.width / 2,size.height/2));
    pWordBg->setPosition(Vec2(size.width / 2,size.height/2));
    
    
    
    auto winsize = Director::getInstance()->getWinSize();
    this->setPosition(Vec2(winsize.width/2-size.width/2, winsize.height/2-size.height/2));
    
    pWordBg->runAction(Sequence::create(
                               DelayTime::create(2),
                               Spawn::create(MoveBy::create(1, Vec2(0, 40)),
                                             FadeOut::create(0.5), NULL),
                               NULL));
    label->runAction(Sequence::create(DelayTime::create(2),
                                            Spawn::create(MoveBy::create(1, Vec2(0, 40)),
                                                          FadeOut::create(0.5), NULL),
                                            NULL));
    runAction(Sequence::create(
                               DelayTime::create(3.5),
                               RemoveSelf::create(), NULL));
    return true;
}



void CLayerMsg::showMsg(std::string msg)
{
    Scene* scene = Director::getInstance()->getRunningScene();
    if (scene == nullptr) {
        return;
    }
    auto layer = CLayerMsg::create(msg);
    scene->addChild(layer, MYDFE_ZORDER_MSG);
}
