USING_NS_CC;

#include "NotificationManager.h"
#include "RichViewController.h"
#include "RichTextManager.h"


static CRichTextManager* g_RichTextManager = nullptr;
//oc type
static UINavigationController *g_nav = nullptr;
static RichViewController *g_richview = nullptr;

CRichTextManager::CRichTextManager()
{
}

CRichTextManager::~CRichTextManager()
{
}

CRichTextManager* CRichTextManager::getInstance()
{
    if (g_RichTextManager == nullptr)
    {
        g_RichTextManager = new CRichTextManager;
    }
    return g_RichTextManager;
}

void CRichTextManager::writeJournal()
{
    _enableRichView(true);
    
    g_richview.title = @"Write Journal";
    g_richview.placeholder = @"Please tap to start editing";
//    [g_richview setCanEditer:true];
}

void CRichTextManager::showJournal(std::string strContext)
{    
    _enableRichView(true);

    NSString*html = [NSString stringWithUTF8String:strContext.c_str()];
    [g_richview setHTML:html];
    g_richview.title = @"";
}

void CRichTextManager::exitRichView()
{
    _enableRichView(false);
}

void CRichTextManager::_enableRichView(bool enable)
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



