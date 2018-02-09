//
//  LayerLogin.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/9.
//

#include "Journal.h"
#include "Define.h"
#include "LoginDefine.h"
#include "LayerSignUp.h"
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
    
    auto bg = LayerColor::create(Color4B(220, 220, 220, 255));
    this->addChild(bg);
    
    
    //logo
    auto logo = Sprite::create("logo.png");
    logo->setPosition(Vec2(m_winSize.width*.5f, m_winSize.height*.8));
    this->addChild(logo);
    auto label = Label::createWithTTF("Login", MY_FONT_ENGLISH, 50);
    label->setPosition(Vec2(logo->getContentSize().width/2, -50));
    label->setTextColor(Color4B(0,0,0,255));
    logo->addChild(label);
    
    
    
    //email
    auto height = m_winSize.height/2;
    auto email = _crateEditBox("login_input.png", "email");
    email->setPosition(Vec2(m_winSize.width/2, height));
    this->addChild(email);
    
    //password
    height -= 120;
    auto password = _crateEditBox("login_input.png", "password");
    password->setPosition(Vec2(m_winSize.width/2, height));
    this->addChild(password);
    
    //login
    height -= 150;
    auto btnLogin = Button::create("login_btn1.png");
    btnLogin->setPosition(Vec2(m_winSize.width/2, height));
    btnLogin->addClickEventListener([](Ref* r){
        //TODO: 发送请求
    });
    this->addChild(btnLogin);
    auto label1 = Label::createWithTTF("Log In", MY_FONT_ENGLISH, 35);
    btnLogin->setTitleLabel(label1);
    
    //signUp
    height -= 120;
    auto btnSiginUp = Button::create("login_btn2.png");
    btnSiginUp->setPosition(Vec2(m_winSize.width/2, height));
    btnSiginUp->addClickEventListener([&](Ref* r){
        //signup
        auto layer = CLayerSignUp::create();
        this->getParent()->addChild(layer);
        this->removeFromParent();
    });
    this->addChild(btnSiginUp);
    auto label2 = Label::createWithTTF("Sign Up", MY_FONT_ENGLISH, 35);
    btnSiginUp->setTitleLabel(label2);
    
//    //find password
//    auto btnFindPassword = Button::create("login_btn2.png");
//    btnFindPassword->setPosition(Vec2(m_winSize.width/2, m_winSize.height/2 - 540));
//    btnFindPassword->addClickEventListener([](Ref* r){
//    });
//    this->addChild(btnFindPassword);
//    auto label3 = Label::createWithTTF("Find Password", MY_FONT_ENGLISH, 35);
//    btnFindPassword->setTitleLabel(label3);

}
