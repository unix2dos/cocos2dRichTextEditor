//
//  ParentController.m
//  Journal-mobile
//
//  Created by liuwei on 2018/2/10.
//

#import "RichViewManager.h"
#import "RichViewController.h"
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
    //    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Edit" style:UIBarButtonItemStylePlain target:self action:@selector(edit)];
    g_richview = [[RichViewController alloc] init];
    g_richview.placeholder = @"enter content";
    
    [self addChildViewController:g_richview];
    [self.view addSubview:g_richview.view];
    
    
    CGSize viewSize = self.view.frame.size;
    auto offX = 10;
    g_textField = [[UITextField alloc]init];
    g_textField.frame = CGRectMake(offX, 60, viewSize.width-offX*2, 60);
    g_textField.placeholder = @"enter title";
    g_textField.font = [UIFont systemFontOfSize:20];
    g_textField.textColor = [UIColor blackColor];
    g_textField.borderStyle = UITextBorderStyleNone;
    g_textField.keyboardType = UIKeyboardTypeDefault;
    [self.view addSubview:g_textField];
    UIView *line = [[UIView alloc] initWithFrame:CGRectMake(0, 60, viewSize.width-offX*2, 1)];
    line.backgroundColor = [UIColor lightGrayColor];
    line.alpha = 0.2f;
    [g_textField addSubview:line];
}



- (void)back {
    //    NSLog(@"%@", [self getHTML]);
    
    //键盘消失
    [g_richview.view endEditing:YES];
    [g_textField endEditing:YES];
    
    //data
    auto& journal = CRichViewManager::getInstance()->getJournal();
    journal.strContent = [[g_richview getHTML] UTF8String];
    journal.strTitle = [g_textField.text UTF8String];
    
    //close
    CRichViewManager::getInstance()->closeJournal();
}



- (void)writeJournal {
    [g_richview setHTML:@""];
    [g_richview setCanEditer:true];
    [g_textField setText:@""];
}


- (void)showJournal {
    auto journal = CRichViewManager::getInstance()->getJournal();
    [g_richview setHTML:[NSString stringWithUTF8String:journal.strContent.c_str()]];
    [g_textField setText:[NSString stringWithUTF8String:journal.strTitle.c_str()]];
    
    auto type = CRichViewManager::getInstance()->getRichViewType();
    [g_richview setCanEditer:(type == RichViewType::show_self)];
    g_textField.enabled = (type == RichViewType::show_self);
}

@end
