//
//  FormController.h
//  iZettleShared
//
//  Created by Mattias Jähnke on 2014-11-24.
//  Copyright (c) 2014 iZettle. All rights reserved.
//

@import UIKit;
#import "FormTableView.h"
#import "FormTableViewDataSource.h"
#import "LocalizedViewController.h"
#import "UIView+Viewport.h"

NS_ASSUME_NONNULL_BEGIN

@class Form;

@interface FormController : LocalizedViewController

// Components
@property (nonatomic, readonly) FormTableView *tableView;
@property (nonatomic, readonly) FormTableViewDataSource *dataSource;

// Settings
@property (nonatomic, strong) Class rootViewClass;
@property (nonatomic, assign) BOOL viewportReactive; // Defaults to YES
@property (nonatomic, assign) BOOL keepBottomContentInsetUponFullViewport; // Don't resize the form if the keyboard hides
@property (nonatomic, assign) BOOL formControllerPrefersStatusBarHidden;
@property (nonatomic, readwrite) UIEdgeInsets tableInsets; // Shortcut to adjusting the tableviews top/bottom and datasources left/right cell inset
@property (nonatomic, assign, getter = shouldFindFirstResponder) BOOL findFirstResponder;
@property (nonatomic, assign) BOOL dynamicPreferredContentSize; // preferredContentSize's will be same as the calculated height of the tableview
@property (nonatomic, assign) CGSize dynamicPreferredContentSizeMaxSize;
// First responder
- (void)setFirstResponderItem:(FormItem *)formItem;

// Form
@property (nonatomic, readwrite, nullable) Form *form;
- (void)setForm:(Form *)form animated:(BOOL)animated;

// Viewport adjustment block. Called after tableview insets are set and the FormTableViewDatasource did its layout
@property (nonatomic, copy, nullable) ViewportBlock scrollViewOffsetAdjustmentBlock;

@end

@interface FormController (ViewportBlocks)
- (ViewportBlock)scrollToFirstResponderBlock;
- (ViewportBlock)scrollToBottomBlock;
@end

@interface FormController (Creation)
+ (instancetype)newForModal; // Returns a FormController with rootViewClass set appropriately
+ (instancetype)newForModalNoBottomPadding; // Returns above but with tableView.contentInset.bottom set to 0
@end

NS_ASSUME_NONNULL_END