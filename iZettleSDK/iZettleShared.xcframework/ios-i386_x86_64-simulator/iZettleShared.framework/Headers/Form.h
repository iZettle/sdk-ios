//
//  Form.h
//  iZettleShared
//
//  Created by Mattias Jähnke on 2013-05-13.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import Foundation;
#import "FormRow.h"

NS_ASSUME_NONNULL_BEGIN

extern NSString *const FormShowDebugKey;

@class FormGroup, FormItem, FormFlexibleSpaceGroup;

@interface Form : NSObject

+ (Form *)form;
+ (Form *)formWithName:(NSString * _Nullable)name;


@property (nonatomic, copy, nullable) NSString *name;
@property (nonatomic, readonly) NSMutableArray<FormGroup *> *groups;
@property (nonatomic, readonly, nullable) NSArray *errors;
@property (nonatomic, readonly) BOOL hasErrors;

- (void)runValidation;

- (void)addGroup:(FormGroup *)group;
- (void)insertObject:(FormGroup *)group inGroupsAtIndex:(NSUInteger)index;

@end


@interface Form (Helpers)


@property (nonatomic, readonly) FormGroup *lastGroup; // will create a group if there is non groups yet

- (FormRow *)addRow;
- (FormRow *)addRowShouldHideBackground:(BOOL)hideBackground;
- (FormRow *)addRowShouldHideBackground:(BOOL)hideBackground shouldHideSeparator:(BOOL)hideSeparator;
- (void)addRow:(FormRow *)row;

- (void)addSeparatorItem;
- (FormRow*)addRowWithItems:(NSArray*)items;
- (FormRow*)addRowWithItems:(NSArray *)items action:(FormRowAction _Nullable)action;
- (FormRow *)addRowWithItem:(FormItem *)item;
- (FormRow *)addRowWithItem:(FormItem *)item floatable:(BOOL)floatable;
- (FormGroup *)addGroupWithHeaderTitle:(NSString *)headerTitle;
- (FormGroup *)addGroupWithHeaderTitle:(NSString *)headerTitle footerTitle:(NSString *)footerTitle;

- (FormItem *)addItem:(FormItem *)item;

- (FormGroup *)addGroup;
- (FormFlexibleSpaceGroup *)addFlexibleHeightGroup;

- (FormRow *)addRowWithTitle:(NSString *)title dingbat:(NSString * _Nullable)dingbat action:(FormRowAction)action;

- (BOOL)displayErrorAlertWithTitle:(NSString *)title;
- (BOOL)displayErrorAlert;

- (void)enumerateRows:(void (^)(FormRow *row, BOOL *stop))rowBlock;
- (void)reversed:(BOOL)reversed enumerateItems:(void (^)(FormItem *item, BOOL *stop))itemBlock;

@end

NS_ASSUME_NONNULL_END