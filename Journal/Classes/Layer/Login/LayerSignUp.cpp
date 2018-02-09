//
//  LayerSignUp.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/9.
//

#include "Journal.h"
#include "Define.h"
#include "HttpManager.h"
#include "CommonUtils.h"
#include "LoginDefine.h"
#include "LayerLogin.h"
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

    auto bg = LayerColor::create(Color4B(220, 220, 220, 255));
    this->addChild(bg);


    //logo
    auto logo = Sprite::create("logo.png");
    logo->setPosition(Vec2(m_winSize.width*.5f, m_winSize.height*.8));
    this->addChild(logo);
    auto label = Label::createWithTTF("SignUp", MY_FONT_ENGLISH, 50);
    label->setPosition(Vec2(logo->getContentSize().width/2, -50));
    label->setTextColor(Color4B(0,0,0,255));
    logo->addChild(label);




    //alias
    auto height = m_winSize.height/2;
    auto alias = _crateEditBox("login_input.png", "alias", false);
    alias->setPosition(Vec2(m_winSize.width/2, height));
    this->addChild(alias);

    //email
    height -= 120;
    auto email = _crateEditBox("login_input.png", "email", false);
    email->setPosition(Vec2(m_winSize.width/2, height));
    this->addChild(email);

    //password
    height -= 120;
    auto password = _crateEditBox("login_input.png", "password", true);
    password->setPosition(Vec2(m_winSize.width/2, height));
    this->addChild(password);

    //signup
    height -= 150;
    auto btnSignUp = Button::create("login_btn1.png");
    btnSignUp->setPosition(Vec2(m_winSize.width/2, height));
    btnSignUp->addClickEventListener([=](Ref* r){
        
        auto strAlias = dynamic_cast<ui::EditBox*>(alias->getChildByName("EditBox"))->getText();
        auto strEmail = dynamic_cast<ui::EditBox*>(email->getChildByName("EditBox"))->getText();
        auto strPass = dynamic_cast<ui::EditBox*>(password->getChildByName("EditBox"))->getText();
        
        //发送请求
        Json::Value root;
        root["username"] = strEmail;
        root["password"] = strPass;
        root["alias"] = strAlias;
        string strJson = buildServeJson(root);
        CHttpManager::getInstance()->HttpPost(MYDEF_URL_SIGNUP, eHttpType::signup, strJson);

    });
    this->addChild(btnSignUp);
    auto label1 = Label::createWithTTF("Sign Up", MY_FONT_ENGLISH, 35);
    btnSignUp->setTitleLabel(label1);

    //back
    height -= 100;
    auto btnBack = Button::create("login_btn1.png");
    btnBack->setPosition(Vec2(m_winSize.width/2, height));
    btnBack->addClickEventListener([&](Ref* r){
        auto layer = CLayerLogin::create();
        this->getParent()->addChild(layer);
        this->removeFromParent();
    });
    this->addChild(btnBack);
    auto label2 = Label::createWithTTF("Back", MY_FONT_ENGLISH, 35);
    btnBack->setTitleLabel(label2);

}


void CLayerSignUp::endWithHttpData(eHttpType myType, HttpResponseInfo rep)
{
    
}
