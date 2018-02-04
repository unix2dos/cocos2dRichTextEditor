//
//  Recorder.cpp
//  ReadingFriends
//
//  Created by Summer on 16/7/20.
//
//

#include "RichText.h"
#include "cocos2d.h"
//#import "ZSSDemoViewController.h"
USING_NS_CC;

CRichText* CRichText::m_pRichText = nullptr;

CRichText::CRichText()
{
}

CRichText::~CRichText()
{
}

CRichText* CRichText::getInstance()
{
    if (m_pRichText == nullptr)
    {
        m_pRichText = new CRichText;
    }
    return m_pRichText;
}

//static ZSSDemoViewController* demo = nullptr;
void CRichText::haha()
{
//    UIViewController *rootViewController = [UIApplication sharedApplication].keyWindow.rootViewController;
//    if (demo)
//    {
//        [rootViewController.view willRemoveSubview:demo.view];
//        demo = nullptr;
//    }
//    else
//    {
//        ZSSDemoViewController *demo = [[ZSSDemoViewController alloc] init];
//        [rootViewController.view addSubview:demo.view];
//    }
}


