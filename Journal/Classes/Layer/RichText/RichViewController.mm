//
//  RichViewController.m
//  ZSSRichTextEditor
//
//  Created by Nicholas Hubbard on 11/29/13.
//  Copyright (c) 2013 Zed Said Studio. All rights reserved.
//

#import "RichViewController.h"
#import "ZSSDemoPickerViewController.h"
#import "DemoModalViewController.h"
#import "RichText.h"

@interface RichViewController ()

@end

@implementation RichViewController


- (void)viewDidLoad {
    [super viewDidLoad];
    self.title = @"Standard";
    self.shouldShowKeyboard = NO;
    self.alwaysShowToolbar = NO;
    self.receiveEditorDidChangeEvents = YES;
//    self.formatHTML = YES;
    [self setPlaceholder:@"This is a placeholder that will show when there is no content(html)"];
    self.enabledToolbarItems = @[ZSSRichTextEditorToolbarBold, ZSSRichTextEditorToolbarH1, ZSSRichTextEditorToolbarParagraph];

    // Export HTML
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Back" style:UIBarButtonItemStylePlain target:self action:@selector(exportHTML)];

    
//    UIButton *b = [[UIButton alloc]initWithButtonType:UIButtonTypeCustom];
//    [b setImage:[UIImage imageNamed:@"BackImage.png"] forState:UIControlStateNormal];
//    [b addTarget:self action:@selector(back:) forControlEvents:UIControlEventTouchUpInside];
//    self.leftBarButtonItem = [[UIBarButtonItem alloc]initWithCustomView:b];
//
    
    NSString *html = @"<div class='test'></div><!-- This is an HTML comment -->"
    "<p>This is a test of the <strong>ZSSRichTextEditor</strong> by <a title=\"Zed Said\" href=\"http://www.zedsaid.com\">Zed Said Studio</a></p>";
    
    [self setHTML:html];
    
}


- (void)showInsertURLAlternatePicker {
    
//    [self dismissAlertView];
//
//    ZSSDemoPickerViewController *picker = [[ZSSDemoPickerViewController alloc] init];
//    picker.demoView = self;
//    UINavigationController *nav = [[UINavigationController alloc] initWithRootViewController:picker];
//    nav.navigationBar.translucent = NO;
//    [self presentViewController:nav animated:YES completion:nil];
    
}


- (void)showInsertImageAlternatePicker {
    
//    [self dismissAlertView];
//
//    ZSSDemoPickerViewController *picker = [[ZSSDemoPickerViewController alloc] init];
//    picker.demoView = self;
//    picker.isInsertImagePicker = YES;
//    UINavigationController *nav = [[UINavigationController alloc] initWithRootViewController:picker];
//    nav.navigationBar.translucent = NO;
//    [self presentViewController:nav animated:YES completion:nil];
    
}


- (void)exportHTML {
    
    NSLog(@"%@", [self getHTML]);
    CRichText::getInstance()->haha();
    
}

- (void)editorDidChangeWithText:(NSString *)text andHTML:(NSString *)html {
    
    NSLog(@"Text Has Changed: %@", text);
    
    NSLog(@"HTML Has Changed: %@", html);
    
}

- (void)hashtagRecognizedWithWord:(NSString *)word {
    
    NSLog(@"Hashtag has been recognized: %@", word);
    
}

- (void)mentionRecognizedWithWord:(NSString *)word {
    
    NSLog(@"Mention has been recognized: %@", word);
    
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
