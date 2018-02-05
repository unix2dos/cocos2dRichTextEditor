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

static RichViewController* controller = nullptr;
void CRichText::haha()
{
    UIViewController *rootViewController = [UIApplication sharedApplication].keyWindow.rootViewController;
    if (controller)
    {
//        [rootViewController.view willRemoveSubview:controller.view];
        //  [self.navigationController popToViewController:(nonnull UIViewController *) animated:(BOOL)];

        [rootViewController dismissViewControllerAnimated:YES completion:nil];
        [controller removeFromParentViewController];
        controller = nullptr;//TODO: 此处应该是删除nav
    }
    else
    {
//        controller = [[RichViewController alloc] init];
//        controller.modalPresentationStyle = UIModalPresentationOverCurrentContext;
//        [rootViewController.view addSubview:controller.view];
//        [rootViewController.navigationController pushViewController:controller animated:YES];
//        [rootViewController presentViewController:controller animated:YES completion:nil];
        
        controller = [[RichViewController alloc] init];
        UINavigationController *nav = [[UINavigationController alloc] initWithRootViewController:controller];
        nav.modalPresentationStyle = UIModalPresentationFormSheet;
        [rootViewController presentViewController:nav animated:YES completion:nil];
    }
}


