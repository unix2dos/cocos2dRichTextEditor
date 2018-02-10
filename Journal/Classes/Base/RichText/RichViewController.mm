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
#import "RichViewManager.h"


@interface RichViewController ()

@end

@implementation RichViewController


- (void)viewDidLoad {
    [super viewDidLoad];
//    self.title = @"";
//    self.placeholder = @"Please tap to start editing";
    self.shouldShowKeyboard = NO;
    self.alwaysShowToolbar = NO;
    self.receiveEditorDidChangeEvents = NO;
    self.formatHTML = NO;
    self.enabledToolbarItems = @[ZSSRichTextEditorToolbarBold
                                 ,ZSSRichTextEditorToolbarItalic
                                 ,ZSSRichTextEditorToolbarUnderline
                                 ,ZSSRichTextEditorToolbarUnorderedList
                                 ,ZSSRichTextEditorToolbarOrderedList
                                 ];
    
    
    // Save
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Back" style:UIBarButtonItemStylePlain target:self action:@selector(back)];
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Edit" style:UIBarButtonItemStylePlain target:self action:@selector(edit)];

//    NSString *html = @"<h1>Large Editor</h1>"
//    [self setHTML:html];
}



- (void)back {
//    NSLog(@"%@", [self getHTML]);
    CRichViewManager::getInstance()->closeJournal([[self getHTML] UTF8String]);
}

- (void)edit {
    [self setCanEditer:true];
}

- (void)editorDidChangeWithText:(NSString *)text andHTML:(NSString *)html {

//    NSLog(@"Text Has Changed: %@", text);
    NSLog(@"HTML Has Changed: %@", html);
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
