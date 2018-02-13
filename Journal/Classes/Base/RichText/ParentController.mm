//
//  ParentController.m
//  Journal-mobile
//
//  Created by liuwei on 2018/2/10.
//

#import "RichViewManager.h"
#import "RichViewController.h"
#import "RichViewDefine.h"
#import "ParentController.h"

@interface ParentController ()

@end


static RichViewController *g_richview = nullptr;
static UITextField *g_textField = nullptr;

@implementation ParentController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.view.backgroundColor = UIColor.whiteColor;
    
    //nav item
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Back" style:UIBarButtonItemStylePlain target:self action:@selector(back)];
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Switch" style:UIBarButtonItemStylePlain target:self action:@selector(edit)];
    self.navigationItem.title = @"Public";
    
    //rich view
    g_richview = [[RichViewController alloc] init];
    g_richview.placeholder = @"enter content";
    [self addChildViewController:g_richview];
    [self.view addSubview:g_richview.view];
    
    


    //title
    int offX = 10;
    CGRect navFrame = self.navigationController.navigationBar.frame;
    int offY = navFrame.size.height + navFrame.origin.y;
    
    CGSize viewSize = self.view.frame.size;
    g_textField = [[UITextField alloc]init];
    g_textField.frame = CGRectMake(offX, offY, viewSize.width-offX*2, RICH_OFFSET_HEIGHT-offY);
    g_textField.placeholder = @"enter title";
    g_textField.font = [UIFont systemFontOfSize:20];
    g_textField.textColor = [UIColor blackColor];
    g_textField.borderStyle = UITextBorderStyleNone;
    g_textField.keyboardType = UIKeyboardTypeDefault;
    [self.view addSubview:g_textField];
    UIView *line = [[UIView alloc] initWithFrame:CGRectMake(0, RICH_OFFSET_HEIGHT-offY, viewSize.width-offX*2, 1)];
    line.backgroundColor = [UIColor lightGrayColor];
    line.alpha = 0.3f;
    [g_textField addSubview:line];
}



- (void)back {
    //keyboard hidden
    [g_richview.view endEditing:YES];
    [g_textField endEditing:YES];
    
    //data
    auto& journal = CRichViewManager::getInstance()->getJournal();
    journal.strContent = [[g_richview getHTML] UTF8String];
    journal.strTitle = [g_textField.text UTF8String];
    
    //close
    CRichViewManager::getInstance()->closeJournal();
}


- (void)edit {
    auto type = CRichViewManager::getInstance()->getRichViewType();
    if (type != RichViewType::show_others)
    {
        auto& journal = CRichViewManager::getInstance()->getJournal();
        journal.isPublic = !journal.isPublic;
        //switch
        [self showSwitch];
    }
}



- (void)writeJournal {
    [g_richview setHTML:@""];
    [g_richview setCanEditer:true];
    [g_textField setText:@""];
    
    //switch
    [self showSwitch];
}


- (void)showJournal {
    auto journal = CRichViewManager::getInstance()->getJournal();
    [g_richview setHTML:[NSString stringWithUTF8String:journal.strContent.c_str()]];
    [g_textField setText:[NSString stringWithUTF8String:journal.strTitle.c_str()]];
    
    auto type = CRichViewManager::getInstance()->getRichViewType();
    [g_richview setCanEditer:(type == RichViewType::show_self)];
    g_textField.enabled = (type == RichViewType::show_self);
    
    //switch
    [self showSwitch];
}

- (void)showSwitch {
    auto journal = CRichViewManager::getInstance()->getJournal();
    auto type = CRichViewManager::getInstance()->getRichViewType();
    if (type == RichViewType::show_others)//其他人不显示
    {
        self.navigationItem.title = @"";
        [self.navigationItem.rightBarButtonItem setEnabled:NO];
        [self.navigationItem.rightBarButtonItem setTintColor: [UIColor clearColor]];
    }
    else
    {
        self.navigationItem.title = journal.isPublic ? @"Public" : @"Private";
        [self.navigationItem.rightBarButtonItem setEnabled:YES];
        [self.navigationItem.rightBarButtonItem setTintColor:nil];
    }
}

@end
