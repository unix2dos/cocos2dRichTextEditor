//
//  iOSRichView.m
//  Journal-mobile
//
//  Created by liuwei on 2018/2/10.
//


#include "RichViewManager.h"
#include "RichViewController.h"
#include "NotificationManager.h"
#include "iOSRichView.h"


iOSRichView::iOSRichView()
:m_richviewType(RichViewType::none)
{
}

iOSRichView::~iOSRichView()
{
}

CRichViewManager* CRichViewManager::getInstance()
{
    if (m_pInstance == nullptr)
    {
        m_pInstance = new iOSRichView;
    }
    return m_pInstance;
}

static UINavigationController *g_nav = nullptr;
static RichViewController *g_richview = nullptr;


void iOSRichView::writeJournal()
{
    if (m_richviewType != RichViewType::none)
    {
        return;
    }
    m_richviewType = RichViewType::write;
    
    _enableRichView(true);
    g_richview.title = @"Write Journal";
    g_richview.placeholder = @"Please tap to start editing";
    [g_richview setCanEditer:true];
}


void iOSRichView::showJournal(std::string strContext)
{
    if (m_richviewType != RichViewType::none)
    {
        return;
    }
    m_richviewType = RichViewType::show_self;
    
    _enableRichView(true);
    NSString*html = [NSString stringWithUTF8String:strContext.c_str()];
    [g_richview setHTML:html];
    g_richview.title = @"";
}

void iOSRichView::closeJournal(std::string strContext)
{
    _enableRichView(false);
 
    if (m_richviewType == RichViewType::write && strContext != "")
    {
        addJournal(strContext);
    }
    m_richviewType = RichViewType::none;
}



void iOSRichView::_enableRichView(bool enable)
{
    UIViewController *root = [UIApplication sharedApplication].keyWindow.rootViewController;
    if (g_nav)
    {
        UIViewController* nav = [root.childViewControllers lastObject];
        [nav willMoveToParentViewController:nil];
        [nav.view removeFromSuperview];
        [nav removeFromParentViewController];
        
        g_nav = nullptr;
        g_richview = nullptr;
        NotificationManager::getInstance()->notify(NOTIFY_TYPE::JOURNAL_BG, (void*)0);
    }
    else
    {
        g_richview = [[RichViewController alloc] init];
        g_nav = [[UINavigationController alloc] initWithRootViewController:g_richview];
        g_nav.navigationBar.translucent = NO;
        [root addChildViewController:g_nav];
        [root.view addSubview:g_nav.view];
        [g_nav didMoveToParentViewController:root];
        
        NotificationManager::getInstance()->notify(NOTIFY_TYPE::JOURNAL_BG, (void*)1);
    }
}



//        CGRect rect = [[UIScreen mainScreen] bounds];
//        CGSize viewSize = rich.view.frame.size;
//        rich.view.frame = CGRectMake(0, 0, viewSize.width, viewSize.height * .5);
//        UITextField* textField = [[UITextField alloc]init];
//        textField.frame = CGRectMake(0, 0, rect.size.width, 50);
//        textField.placeholder = @"请输入标题";
//        textField.font = [UIFont systemFontOfSize:20];
//        textField.textColor = [UIColor blackColor];
//        textField.borderStyle = UITextBorderStyleRoundedRect;
//        textField.keyboardType = UIKeyboardTypeDefault;
