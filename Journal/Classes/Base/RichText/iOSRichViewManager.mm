//
//  iOSRichViewManager.m
//  Journal-mobile
//
//  Created by liuwei on 2018/2/10.
//


#include "RichViewManager.h"
#include "RichViewController.h"
#include "NotificationManager.h"
#include "iOSRichViewManager.h"
#import "ParentController.h"

static UINavigationController *g_naviview = nullptr;
static ParentController *g_parent = nullptr;

iOSRichViewManager::iOSRichViewManager()
:m_richviewType(RichViewType::none)
{
}

iOSRichViewManager::~iOSRichViewManager()
{
}


CRichViewManager* CRichViewManager::getInstance()
{
    if (m_pInstance == nullptr)
    {
        m_pInstance = new iOSRichViewManager;
    }
    return m_pInstance;
}


void iOSRichViewManager::initRichView()
{
    UIViewController *root = [UIApplication sharedApplication].keyWindow.rootViewController;
    g_parent = [[ParentController alloc] init];
    g_naviview = [[UINavigationController alloc] initWithRootViewController:g_parent];
    [root addChildViewController:g_naviview];
    [root.view addSubview:g_naviview.view];
    [g_naviview didMoveToParentViewController:root];
    g_naviview.view.hidden = true;
}


void iOSRichViewManager::writeJournal()
{
    if (m_richviewType != RichViewType::none)
    {
        return;
    }
    m_richviewType = RichViewType::write;
    
    _enableRichView(true);
    [g_parent writeJournal];
}


void iOSRichViewManager::showJournal(std::string strContext)
{
    if (m_richviewType != RichViewType::none)
    {
        return;
    }
    m_richviewType = RichViewType::show_self;
    
    _enableRichView(true);
    [g_parent showJournal:[NSString stringWithUTF8String:strContext.c_str()]];
}


void iOSRichViewManager::closeJournal(std::string strContext)
{
    if (m_richviewType == RichViewType::write && strContext != "")
    {
        addJournal(strContext);
    }
    
    _enableRichView(false);
    m_richviewType = RichViewType::none;
}



void iOSRichViewManager::_enableRichView(bool enable)
{
    g_naviview.view.hidden = !enable;
}

//void iOSRichViewManager::_enableRichView(bool enable)
//{
//    UIViewController *root = [UIApplication sharedApplication].keyWindow.rootViewController;
//    if (g_naviview)
//    {
//        UIViewController* nav = [root.childViewControllers lastObject];
//        [nav willMoveToParentViewController:nil];
//        [nav.view removeFromSuperview];
//        [nav removeFromParentViewController];
//
//        g_naviview = nullptr;
//        g_richview = nullptr;
//        NotificationManager::getInstance()->notify(NOTIFY_TYPE::JOURNAL_BG, (void*)0);
//    }
//    else
//    {
//        g_richview = [[RichViewController alloc] init];
//        g_naviview = [[UINavigationController alloc] initWithRootViewController:g_richview];
//        g_naviview.navigationBar.translucent = NO;
//        [root addChildViewController:g_naviview];
//        [root.view addSubview:g_naviview.view];
//        [g_naviview didMoveToParentViewController:root];
//
//        NotificationManager::getInstance()->notify(NOTIFY_TYPE::JOURNAL_BG, (void*)1);
//    }
//}
