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
                                 ,ZSSRichTextEditorToolbarParagraph
                                 ];
    
    
    // Save
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Back" style:UIBarButtonItemStylePlain target:self action:@selector(exportHTML)];


    
    
    NSString *html = @"";
    [self setHTML:html];

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
