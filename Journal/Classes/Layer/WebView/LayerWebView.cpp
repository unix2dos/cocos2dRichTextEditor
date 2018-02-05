//
//  LayerWebView.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/3.
//


#include "Config.h"
#include "ui/CocosGUI.h"
#include "LayerWebView.h"

CLayerWebView::CLayerWebView(){
    
}


CLayerWebView::~CLayerWebView(){
    
}


bool CLayerWebView::init()
{
    if(!Layer::init()){
       return false;
    }

    _initUI();

    return true;
}


void CLayerWebView::_initUI()
{
    Size winSize = Director::getInstance()->getVisibleSize();
    _webView = cocos2d::experimental::ui::WebView::create();
    _webView->setPosition(winSize/2);
    _webView->setContentSize(winSize);
//    _webView->loadURL("https://www.baidu.com");
    _webView->loadFile("Test.html");
    _webView->setScalesPageToFit(true);

    _webView->setOnShouldStartLoading(CC_CALLBACK_2(CLayerWebView::onWebViewShouldStartLoading, this));
    _webView->setOnDidFinishLoading(CC_CALLBACK_2(CLayerWebView::onWebViewDidFinishLoading, this));
    _webView->setOnDidFailLoading(CC_CALLBACK_2(CLayerWebView::onWebViewDidFailLoading, this));

    this->addChild(_webView);
}



bool CLayerWebView::onWebViewShouldStartLoading(experimental::ui::WebView *sender, const std::string &url)
{
    CCLOG("onWebViewShouldStartLoading, url is %s", url.c_str());
    //don't do any OpenGL operation here!! It's forbidden!
    return true;
}

void CLayerWebView::onWebViewDidFinishLoading(experimental::ui::WebView *sender, const std::string &url)
{
//    auto node = (ui::Button*)this->getChildByName("evalJs");
//    node->setTitleText("start loading...");
    CCLOG("onWebViewDidFinishLoading, url is %s", url.c_str());
}

void CLayerWebView::onWebViewDidFailLoading(experimental::ui::WebView *sender, const std::string &url)
{
    CCLOG("onWebViewDidFailLoading, url is %s", url.c_str());
}

