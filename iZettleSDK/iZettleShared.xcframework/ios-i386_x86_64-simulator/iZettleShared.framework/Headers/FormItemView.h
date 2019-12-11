//
//  FormBaseView.h
//  iZettle
//
//  Created by Mattias Jähnke on 2013-04-25.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import UIKit;
#import "FormItem.h"

// Space left and right of normal text in form cells
#define INPUT_HORIZONTAL_PADDING ([UIDevice isCurrentlyRegularSized] ? 8 : 6)

typedef void (^FormValueChangedBlock)(NSString *key, id value);

@interface FormItemView : UIView

+ (void)registerFormItemViewClass:(Class)itemViewClass forItemType:(FormItemType)formItemType;
+ (Class)formItemViewClassForItemType:(FormItemType)formItemType;

- (void)_sharedInit;
- (void)startSpinner;
- (void)stopSpinner;
- (void)setupConstraintsForSpinner:(UIView *)spinner;
- (void)prepareForReuse;

@property (nonatomic, strong) FormItem *model;
@property (nonatomic, assign) BOOL highlighted;

- (void)modelDidUpdateWithTitle:(NSString *)title;
- (void)modelDidUpdateWithValue:(id)value;
- (void)modelDidUpdateEnabled:(BOOL)enabled;

@property (nonatomic, readonly) BOOL addMarginsAtCellEnds;

- (void)updateValueWithBlock:(void(^)(void))updateBlock;

@end

@interface FormItemView (Styling)
- (void)setFont:(UIFont *)font;
- (void)setTextColor:(UIColor *)color;
- (void)setHighlightedTextColor:(UIColor *)color;
- (void)setSeparatorColor:(UIColor *)color;
@end
