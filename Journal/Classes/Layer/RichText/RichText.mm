//
//  Recorder.cpp
//  ReadingFriends
//
//  Created by Summer on 16/7/20.
//
//

USING_NS_CC;
#include "Journal.h"
#include "RichViewController.h"
#include "RichText.h"


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


static UINavigationController *nav = nullptr;
void CRichText::haha()
{
    UIViewController *root = [UIApplication sharedApplication].keyWindow.rootViewController;
    if (nav)
    {
        UIViewController *vc = [root.childViewControllers lastObject];
        [vc willMoveToParentViewController:nil];
        [vc.view removeFromSuperview];
        [vc removeFromParentViewController];
        nav = nullptr;
    }
    else
    {
        cocos2d::Size winSize = Director::getInstance()->getWinSize();
        
        RichViewController* rich = [[RichViewController alloc] init];
        nav = [[UINavigationController alloc] initWithRootViewController:rich];
        nav.navigationBar.translucent = NO;
        [root addChildViewController:nav];
//        nav.view.frame = CGRectMake(0, 0, 400, 500);
        
        [root.view addSubview:nav.view];
        [nav didMoveToParentViewController:root];
    }
}


