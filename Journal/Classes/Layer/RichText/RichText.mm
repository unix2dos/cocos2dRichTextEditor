//
//  Recorder.cpp
//  ReadingFriends
//
//  Created by Summer on 16/7/20.
//
//

#include "RichText.h"
#include "cocos2d.h"
#include "RichViewController.h"
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

static RichViewController* demo = nullptr;
void CRichText::haha()
{
    UIViewController *rootViewController = [UIApplication sharedApplication].keyWindow.rootViewController;
    if (demo)
    {
        [rootViewController.view willRemoveSubview:demo.view];
        demo = nullptr;
    }
    else
    {
        demo = [[RichViewController alloc] init];
        [rootViewController.view addSubview:demo.view];
    }
}


