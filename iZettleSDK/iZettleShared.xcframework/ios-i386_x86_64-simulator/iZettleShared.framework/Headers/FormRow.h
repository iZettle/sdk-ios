//
//  FormRow.h
//  iZettleShared
//
//  Created by Mattias Jähnke on 2013-05-13.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

@class FormItem;

/*
 Item Layout
 
 A row will layout it's items from left to right.
 The leftmost item will always be tied to the row's left side.
 The rightmost item will always be tied to the row's right side.
 A single item in a row will be bound to both left and right sides and hence will be stretched.
 The width of items will depend on its constraints and intrinsic sizes.
 A FormItemView responds to addMarginsAtCellEnds (BOOL). Large buttons typically returns FALSE and text fields and labels TRUE.
 When addMarginsAtCellEnds returns true a margin (10 on iPad, 8 on iPhone) is added to the left and/or right of an item if it's background begins and/or ends.
 
 
 Floating
 
 An item can be floatable. If more then one item in a row is floatable all floatable items are set to the same width.
 By setting the floatingWeight on an item the weight between floatable items can be adjusted.
 
 
 Background and Separator Layout
 
 An item can hide it's background. If a row hides it background all items backgrounds are hidden as well.
 Only items with it's background not hidden will display a cell background and separator. 

*/

typedef BOOL (^FormRowAction)(void);

@interface FormRow : NSObject

@property (nonatomic, assign, getter = isVisible) BOOL visible;

@property (nonatomic, readonly) NSMutableArray<FormItem*> *items;
@property (nonatomic, readonly) BOOL hasContentWithVariableHeight;
@property (nonatomic, readonly) BOOL hasAllContentWithVariableHeight;

@property (nonatomic, assign) float preferredRowHeight;
@property (nonatomic, assign) float preferredInset; // Horizontal

@property (nonatomic, readonly) NSArray *errors;
@property (nonatomic, readonly) BOOL hasErrors;

- (void)runValidation;

@property (nonatomic, assign) BOOL enabled;
@property (nonatomic, copy) FormRowAction action; // should return YES to keep selection.


@property (nonatomic, copy) void (^reorderBlock)(NSIndexPath *oldIndexPath, NSIndexPath *newIndexPath);

- (FormItem *)addItem:(FormItem *)item;

@property (nonatomic, assign, getter = shouldHideBackground) BOOL hideBackground;
@property (nonatomic, assign, getter = shouldHideSeparator) BOOL hideSeparator;

@property (nonatomic, readonly) BOOL allItemsCanBeReused; // Can all items be reused

@end

@interface FormRow (Helpers)
+ (FormRow *)formRowWithItems:(NSArray<FormItem*> *)items;
- (FormItem * _Nullable)itemWithTag:(NSInteger)tag;
@end

NS_ASSUME_NONNULL_END
