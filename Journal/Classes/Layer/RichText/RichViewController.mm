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
    self.title = @"写日记";
    self.shouldShowKeyboard = NO;
    self.alwaysShowToolbar = NO;
    self.receiveEditorDidChangeEvents = NO;
    self.formatHTML = YES;
    self.placeholder = @"Please tap to start editing";
    self.toolbarItemTintColor = [UIColor redColor];
    self.toolbarItemSelectedTintColor = [UIColor blackColor];
    self.enabledToolbarItems = @[ZSSRichTextEditorToolbarBold
                                 ,ZSSRichTextEditorToolbarItalic
                                 ,ZSSRichTextEditorToolbarUnderline
                                 ,ZSSRichTextEditorToolbarUnorderedList
                                 ,ZSSRichTextEditorToolbarOrderedList
//                                 ,ZSSRichTextEditorToolbarTextColor
//                                 ,ZSSRichTextEditorToolbarH1
//                                 ,ZSSRichTextEditorToolbarH2
//                                 ,ZSSRichTextEditorToolbarH3
//                                 ,ZSSRichTextEditorToolbarH4
//                                 ,ZSSRichTextEditorToolbarH5
//                                 ,ZSSRichTextEditorToolbarH6
//                                 ,ZSSRichTextEditorToolbarParagraph
                                 ];
    
    
    // Export HTML
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Back" style:UIBarButtonItemStylePlain target:self action:@selector(exportHTML)];


    NSString *html = @"";
    [self setHTML:html];
    
    
    
    
//    self.view.backgroundColor = [UIColor whiteColor];
//    UIBarButtonItem *save = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemSave target:self action:@selector(saveURL)];
//    self.navigationItem.rightBarButtonItem = save;
//    
//    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemCancel target:self action:@selector(cancel)];
//    
//    self.textField = [[UITextField alloc] initWithFrame:CGRectMake(20, 20, self.view.frame.size.width - 40, 40)];
//    self.textField.text = !self.isInsertImagePicker ? @"http://www.apple.com" : @"http://fineprintnyc.com/images/blog/history-of-apple-logo/apple-logo-2.jpg";
//    self.textField.layer.borderColor = [UIColor grayColor].CGColor;
//    self.textField.layer.borderWidth = 0.5f;
//    self.textField.clearButtonMode = UITextFieldViewModeAlways;
//    [self.view addSubview:self.textField];
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
