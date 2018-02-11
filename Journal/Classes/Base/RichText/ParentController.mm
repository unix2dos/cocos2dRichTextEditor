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

@implementation ParentController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.view.backgroundColor = UIColor.whiteColor;
    
    //bar item
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Back" style:UIBarButtonItemStylePlain target:self action:@selector(back)];
    //    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Edit" style:UIBarButtonItemStylePlain target:self action:@selector(edit)];
    g_richview = [[RichViewController alloc] init];
    g_richview.placeholder = @"Please tap to start editing";
    
    [self addChildViewController:g_richview];
    [self.view addSubview:g_richview.view];
}



- (void)back {
    //    NSLog(@"%@", [self getHTML]);
    [g_richview.view endEditing:YES];//键盘消失
    
    auto& journal = CRichViewManager::getInstance()->getJournal();
    journal.strContent = [[g_richview getHTML] UTF8String];
    
    CRichViewManager::getInstance()->closeJournal();
}



- (void)writeJournal {
    [g_richview setHTML:@""];
    [g_richview setCanEditer:true];
}


- (void)showJournal {
    auto journal = CRichViewManager::getInstance()->getJournal();
    [g_richview setHTML:[NSString stringWithUTF8String:journal.strContent.c_str()]];
    
    auto type = CRichViewManager::getInstance()->getRichViewType();
    [g_richview setCanEditer:(type == RichViewType::show_self)];
}



//    g_richview.placeholder = @"enter context";
//    CGPoint pos = g_richview.view.center;
//    g_richview.view.center = CGPointMake(pos.x, pos.y + 150);
//    CGSize size = g_richview.view.frame.size;
//    g_richview.view.frame.size = CGSizeMake(size.width, size.height-150);




//    CGFloat height = g_naviview.navigationBar.frame.size.height*2;
//    CGSize viewSize = parent.view.frame.size;
//    UITextField *textField = [[UITextField alloc] initWithFrame:CGRectMake(0, 80, viewSize.width, 50)];
//    textField.borderStyle = UITextBorderStyleNone;
//    textField.font = [UIFont systemFontOfSize:20];
//    textField.placeholder = @"enter title";
//    textField.autocorrectionType = UITextAutocorrectionTypeNo;
//    textField.keyboardType = UIKeyboardTypeDefault;
//    textField.returnKeyType = UIReturnKeyDone;
//    textField.clearButtonMode = UITextFieldViewModeWhileEditing;
//    textField.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;
//    [parent.view addSubview:textField];


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


@end
