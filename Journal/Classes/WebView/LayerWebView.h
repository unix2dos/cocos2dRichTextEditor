//
//  LayerWebView.hpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/3.
//

#ifndef LayerWebView_hpp
#define LayerWebView_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

class CLayerWebView: public cocos2d::Layer
{
public:
    CLayerWebView();
    virtual ~CLayerWebView();
    CREATE_FUNC(CLayerWebView);
    bool init() override;
    bool onWebViewShouldStartLoading(cocos2d::experimental::ui::WebView *sender, const std::string &url);
    void onWebViewDidFinishLoading(cocos2d::experimental::ui::WebView *sender, const std::string &url);
    void onWebViewDidFailLoading(cocos2d::experimental::ui::WebView *sender, const std::string &url);
private:
    void _initUI();
    
private:
    cocos2d::experimental::ui::WebView *_webView;
};



#endif /* LayerWebView_hpp */
