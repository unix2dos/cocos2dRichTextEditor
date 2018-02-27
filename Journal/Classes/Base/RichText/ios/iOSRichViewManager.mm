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
    CRichViewManager::initRichView();
    
    UIViewController *root = [UIApplication sharedApplication].keyWindow.rootViewController;
    g_parent = [[ParentController alloc] init];
    g_naviview = [[UINavigationController alloc] initWithRootViewController:g_parent];
    [root addChildViewController:g_naviview];
    [root.view addSubview:g_naviview.view];
    [g_naviview didMoveToParentViewController:root];
    g_naviview.view.hidden = true;
}



void iOSRichViewManager::newJournal()
{
    CRichViewManager::newJournal();
    
    _enableRichView(true);
    [g_parent writeJournal];
}

void iOSRichViewManager::showJournal(const Journal_Info& info, bool myself)
{
    CRichViewManager::showJournal(info, myself);
    
    _enableRichView(true);
    [g_parent showJournal];
}


void iOSRichViewManager::closeJournal()
{
    CRichViewManager::closeJournal();
    _enableRichView(false);
}


void iOSRichViewManager::_enableRichView(bool enable)
{
    g_naviview.view.hidden = !enable;
}
