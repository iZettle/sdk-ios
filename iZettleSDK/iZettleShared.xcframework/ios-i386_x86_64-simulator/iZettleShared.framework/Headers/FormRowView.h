//
//  FormItemViewContainer.h
//  iZettleShared
//
//  Created by Mattias Jähnke on 2013-05-14.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import UIKit;
#import "SeparatorView.h"
#import "IZLabel.h"

extern CGFloat const kFormRowViewDefaultIPadHeight;
extern CGFloat const kFormRowViewDefaultIPhone4Height;
extern CGFloat const kFormRowViewDefaultIPhoneHeight;

@class FormItemView, FormRow, FormItem;

@interface FormRowView : UIView

- (void)_sharedInit;

@property (nonatomic, assign) BOOL first;
@property (nonatomic, assign) BOOL last;

- (void)setFirst:(BOOL)first last:(BOOL)last;

@property (nonatomic, assign, getter = isSelected) BOOL selected;
@property (nonatomic, assign, getter = isHighlighted) BOOL highlighted;

@property (nonatomic, strong) FormRow *model;

@property (nonatomic, readonly) UIImage *backgroundImage;
@property (nonatomic, readonly) UIImage *selectedBackgroundImage;
@property (nonatomic, readonly) UIImage *highlightedBackgroundImage;

@property (nonatomic, assign) UIEdgeInsets contentInsets;
@property (nonatomic, assign) CGFloat preferredHeight;
- (void)setContentInsetsValue:(NSValue *)contentInsets UI_APPEARANCE_SELECTOR;

- (void)iterateFormItemViews:(void(^)(FormItemView *itemView))block;

@property (nonatomic, readonly) UIColor *separatorColor;
@property (nonatomic, readonly) UIEdgeInsets separatorInsets;

+ (instancetype)formRowViewWithModel:(FormRow *)formRow;

- (void)populateWithModel:(FormRow *)formRow;

@end


@interface MenuFormRowView : FormRowView
@end

@interface SmallerMenuFormRowView : MenuFormRowView
@end

@interface SimpleFormRowView : FormRowView
@end

@interface ErrorFormRowView : FormRowView
@end

@interface OutlineFormRowView : FormRowView
@end

@interface PopoverFormRowView : FormRowView
@end

@interface LineSeparatedFormRowView : FormRowView
@end

// ********* Section header/footer *********

@interface FormSectionHeader : UITableViewHeaderFooterView
@property (nonatomic, strong) UILabel *headerTextLabel;
- (void)sharedInit;
@end

@interface SectionHeader : FormSectionHeader;
@end

@interface FormSectionFooter : UITableViewHeaderFooterView
@property (nonatomic, strong) SmallLabel *footerTextLabel;

- (CGFloat)heightForWidth:(CGFloat)width withFont:(UIFont *)font;
@end
