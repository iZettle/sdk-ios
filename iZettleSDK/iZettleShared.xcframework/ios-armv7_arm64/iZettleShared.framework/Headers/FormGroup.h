//
//  FormGroup.h
//  iZettleShared
//
//  Created by Mattias Jähnke on 2013-05-13.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import Foundation;
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

@class FormRow;
@class FormItem, FormValueItem;

@interface FormGroup : NSObject

@property (nonatomic, assign, getter = isVisible) BOOL visible;

@property (nonatomic, readonly) NSMutableArray<FormRow *> *rows;

@property (nonatomic, readonly) NSArray *errors;
@property (nonatomic, readonly) BOOL hasErrors;

- (void)runValidation;

@property (nonatomic, copy) NSString *headerTitle;
@property (nonatomic, copy) NSString *footerTitle;

@property (nonatomic, assign) CGFloat emptyFooterHeight;

@property (nonatomic, assign) float preferredRowHeight;

- (void)addRow:(FormRow *)row;

- (void)dependingFormValueItem:(FormValueItem *)item regex:(NSString *)pattern keyPath:(NSString *)keyPath;

// KVO
- (NSInteger)countOfRows;
- (id)objectInRowsAtIndex:(NSInteger)index;
- (void)insertObject:(FormRow *)row inRowsAtIndex:(NSInteger)index;
- (void)removeObjectFromRowsAtIndex:(NSInteger)index;

@end


@interface FormFlexibleSpaceGroup : FormGroup

+ (instancetype)flexibleSpaceGroupWithWeight:(CGFloat)weight;

@property (nonatomic, assign) CGFloat weight;

@end


@interface FormGroup (Helpers)

+ (FormGroup *)formGroupWithoutTrailingSpace;

@property (nonatomic, readonly) FormRow *lastRow;
@property (nonatomic, readonly) BOOL isFlexibleSpaceGroup;

- (FormRow *)addRow;
- (FormItem *)addItem:(FormItem *)item;

@end

NS_ASSUME_NONNULL_END