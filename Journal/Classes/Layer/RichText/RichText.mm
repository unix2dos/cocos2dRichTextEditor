//
//  Recorder.cpp
//  ReadingFriends
//
//  Created by Summer on 16/7/20.
//
//

USING_NS_CC;

#include "NotificationManager.h"
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
        
        NotificationManager::getInstance()->notify(NOTIFY_TYPE::JOURNAL_BG, (void*)0);
    }
    else
    {
        RichViewController* rich = [[RichViewController alloc] init];
        nav = [[UINavigationController alloc] initWithRootViewController:rich];
        nav.navigationBar.translucent = NO;
        [root addChildViewController:nav];
        
        CGRect rect = [[UIScreen mainScreen] bounds];
//        CGSize viewSize = rich.view.frame.size;
//        rich.view.frame = CGRectMake(0, 0, viewSize.width, viewSize.height * .5);
//        UITextField* textField = [[UITextField alloc]init];
//        textField.frame = CGRectMake(0, 0, rect.size.width, 50);
//        textField.placeholder = @"请输入标题";
//        textField.font = [UIFont systemFontOfSize:20];
//        textField.textColor = [UIColor blackColor];
//        textField.borderStyle = UITextBorderStyleRoundedRect;
//        textField.keyboardType = UIKeyboardTypeDefault;
//        [rich.view addSubview:textField];
        
        
        
        [root.view addSubview:nav.view];
        [nav didMoveToParentViewController:root];
        
        NotificationManager::getInstance()->notify(NOTIFY_TYPE::JOURNAL_BG, (void*)1);
    }
}


