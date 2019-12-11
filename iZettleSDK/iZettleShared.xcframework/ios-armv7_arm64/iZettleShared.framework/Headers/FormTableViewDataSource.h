//
//  FormTableViewDataSource.h
//  iZettleShared
//
//  Created by Måns Bernhardt on 2013-05-15.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import UIKit;
#import "FormGroup.h"
#import "FormRow.h"
#import "Form.h"

@class Form;
@class FormTableViewCell, FormTableView;


// Left/right should be -5000 to simulate Apple-defaults - and allow 0 as padding.
#define APPLE_DEFAULT_HORIZONTAL_PADDING (-5000)


@interface FormTableViewDataSource : NSObject <UITableViewDataSource, UITableViewDelegate>

@property (nonatomic, assign) BOOL disableAnimationsByDefault;
@property (nonatomic, assign) CGFloat rowHeight;
@property (nonatomic, strong) Form *form;
- (void)setForm:(Form *)form animated:(BOOL)animated;

/// Automatically disable the tableviews scrolling if the content is smaller than the screen
@property (nonatomic, assign) BOOL automaticScrollDisable;

// The tableInsets won't affect top and bottom - only left and right!
+ (UIEdgeInsets)defaultTableInsets;
@property (nonatomic, assign) UIEdgeInsets tableInsets;

@property (nonatomic, assign) UITableViewRowAnimation rowAnimation;
@property (nonatomic, strong) Class rowViewClass;

@property (nonatomic, assign, getter = isScrollingEnabled) BOOL scrollingEnabled;
@property (nonatomic, assign, getter = shouldPinToBottom) BOOL pinToBottom;
@property (nonatomic, assign, getter = shouldDisplayInlineErrors) BOOL displayInlineErrors;

- (void)setNeedsUpdate;
- (void)updateIfNeeded;
- (void)updateForm;
- (void)updateFormAnimated:(BOOL)animated;

- (void)updateScrollEnabled;

- (NSInteger)sectionForGroup:(FormGroup *)formGroup;
- (NSIndexPath *)indexPathForRow:(FormRow*)formRow;

- (CGRect)rectForGroup:(FormGroup *)formGroup;
- (CGRect)rectForRow:(FormRow *)formRow;

@property (nonatomic, weak) FormTableView *tableView;
@property (nonatomic, readonly) CGFloat tableHeight;
@property (nonatomic, copy) dispatch_block_t tableHeightChangedBlock;

- (CGFloat)tableHeightWithFlexibleGroupHeight:(CGFloat)flexibleGroupHeight; // returns the tableHeight property with a set height for every spacegroup

- (CGFloat)calcTableHeight;

- (void)selectRowAtIndexPath:(NSIndexPath *)indexPath animated:(BOOL)animated scrollPosition:(UITableViewScrollPosition)scrollPosition;

- (void)makeItemFirstResponder:(FormItem *)next;

- (void)becomeFirstResponder;

@property (nonatomic, readonly) BOOL willBecomeFirstResponder;

@end


@interface FormGroup (FormGroupAdditions)

+ (FormGroup *)formGroupWithRowClass:(Class)rowClass;
- (Class)_formGroupRowClass;

@end