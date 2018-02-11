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



@interface RichViewController ()

@end

@implementation RichViewController

//理论上这个类不应该变化了
- (void)viewDidLoad {
    [super viewDidLoad];

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
    //    self.title = @"";
    //    self.placeholder = @"Please tap to start editing";
    //    NSString *html = @"<h1>Large Editor</h1>"
    //    [self setHTML:html];
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
