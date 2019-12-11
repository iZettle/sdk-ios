//
//  FormItem.h
//  iZettleShared
//
//  Created by Mattias Jähnke on 2013-05-13.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import Foundation;
@import UIKit;
#import "NSObject+KVOHelper.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, FormItemType) {
    FormItemTypeInputPlain,                         // Produces NSString
    FormItemTypeInputNumeric,                       // Produces NSString (only digits)
    FormItemTypeInputNumber,                        // Produces NSDecimalNumber [0,00]
    FormItemTypeInputNumberIntegerCalculator,       // Produces NSDecimalNumber (integer) [5] (Simulates the behavior of a calculator)
    FormItemTypeInputEmail,
    FormItemTypeInputPassword,
    FormItemTypeInputSecure,
    FormItemTypeInputNumericSecure,
    FormItemTypeInputSwitch,
    FormItemTypeInputOptions,
    FormItemTypeInputAmount,
    
    FormItemTypeStaticLabel,
    FormItemTypeStaticDetailsLabel,
    FormItemTypeStaticMultilineLabel,
    FormItemTypeStaticDingbatLabel,
    FormItemTypeStaticBoldDingbatLabel,
    FormItemTypeStaticSeparator,
    FormItemTypeStaticSpacer,
    FormItemTypeStaticTitleValue,
    FormItemTypeStaticTitleSubtitle,
    FormItemTypeStaticImageView,
    
    FormItemTypeView,
    
    FormItemTypeSingleActionButton,
    FormItemTypeActionButton,
    FormItemTypeSecondaryButton,
    FormItemTypeDestructiveButton,
    FormItemTypeDestructiveActionButton, // Should be used when "destruction" is the main action in a view
    FormItemTypeLinkButton,
    
    FormItemTypeRoundedButton,
    FormItemTypeRoundedGreenButton,
    FormItemTypeRoundedActionButton,
    FormItemTypeSmallButton,
};


typedef BOOL(^ValidationBlock)(id value);

@class FormValueItem;

/*
    Layout
    See "FormRow.h" for layout of items in a row.
*/

@interface FormItem : NSObject

+ (instancetype)formItemWithType:(FormItemType)itemType;
+ (instancetype)formItemWithType:(FormItemType)itemType title:(NSString *)title ;

- (void)dependingFormValueItem:(FormValueItem *)item regex:(NSString *)pattern keyPath:(NSString *)keyPath;

@property (nonatomic, assign, getter = isFirstResponder) BOOL firstResponder;
@property (nonatomic, assign, getter = isSpinnerAnimating) BOOL animateSpinner;
@property (nonatomic, assign) BOOL enabled;
@property (nonatomic, assign) BOOL stepNextIfValid;
@property (nonatomic, assign) BOOL stepPreviousOnBack;
@property (nonatomic, assign) FormItemType type;
@property (nonatomic, assign, getter = isVisible) BOOL visible;
@property (nonatomic, copy) NSString *title;

@property (nonatomic, strong, nullable) NSArray *manualErrors;
@property (nonatomic, readonly) NSArray *errors;
@property (nonatomic, readonly) BOOL hasErrors;

// A floatable item will be set to use the same width as other floatable items in a row (see FormRow.h)
@property (nonatomic, assign, getter = isFloatable) BOOL floatable;

// A floatable item's weight in comparison to other floatable items. defaults to 1.0.  (see FormRow.h)
@property (nonatomic, assign) CGFloat floatingWeight;

@property (nonatomic, assign, getter = shouldHideBackground) BOOL hideBackground;

@property (nonatomic, readonly) BOOL hasContentWithVariableHeight;
@property (nonatomic, strong) NSDictionary *userInfo;

@property (nonatomic, assign) BOOL viewCanBeReused; /// Some items that setup block callbacks etc won't be easly reused.

- (void)runValidation;
- (instancetype)floatableItem;

@property (nonatomic, assign) NSInteger tag;

@end

extern NSString *const FormValueItemShouldStepToNextNotification;
extern NSString *const FormValueItemShouldStepToPreviousNotification;

typedef BOOL (^ValueReturnBlock)(void);
typedef void (^EditingStateChangedBlock)(UIControlEvents editingState);
@interface FormValueItem : FormItem
@property (nonatomic, strong) id value; // Use KVO to listen to changes.
@property (nonatomic, assign) BOOL isEditing; // Use KVO to listen to changes.
@property (nonatomic, copy) ValueReturnBlock valueReturnBlock; // keyboard return is pressed. return true if handled.
@property (nonatomic, copy) EditingStateChangedBlock editingStateChangedBlock; // editing state changed, i.e keyboard disapeared or appeared

@property (nonatomic, readonly) NSArray *validationErrors;

+ (FormValueItem *)formItemWithType:(FormItemType)type title:(NSString *)title value:(id)value;
+ (FormValueItem *)formItemWithType:(FormItemType)type title:(NSString *)title value:(id)value valueChangedBlock:(KVOBlock)valueChangedBlock;

+ (FormValueItem *)formValueItemWithType:(FormItemType)type title:(NSString *)title value:(id)value valueChangedBlock:(void(^)(id newValue))valueChangedBlock; // Swift compatibility

- (void)addValidationBlock:(ValidationBlock)validationBlock withErrorMessage:(NSString *)errorMessage;
- (void)removeAllValidationBlocks;
- (BOOL)canBecomeFirstResponder;

@end


@interface FormOptionsItem : FormValueItem
@property (nonatomic, strong) NSArray *options;
@end


@interface FormActionItem : FormItem
@property (nonatomic, copy) dispatch_block_t action;
@end

/*
    FormCustomViewItem is for adding custom views to a form row.
    You can add padding around the view by setting an edgeInset.
    A floating custom view be stretch to use it's size set by the row.
    A non floating custom view will try to maintain it's width if set or its intrinsic size. It will center in its container.
 */

@interface FormCustomViewItem : FormItem
@property (nonatomic, strong) UIView *view;
@property (nonatomic, strong) UIView *firstResponderView;
@property (nonatomic, assign) UIEdgeInsets edgeInsets;
@property (nonatomic, assign) BOOL addMarginsAtCellEnds; // see FormRow.h
@property (nonatomic, assign) BOOL useDefaultContentHeight;

@end

@interface FormItem (Helpers)

//+ (FormItem *)formArrowItem;
+ (instancetype)formItemSeparator;
+ (instancetype)formItemSpacerWithSize:(CGSize)size;
+ (instancetype)formItemSpacerWithWidth:(CGFloat)width;
+ (instancetype)formItemSpacerWithHeight:(CGFloat)height;

+ (instancetype)floatingFormItemSpacer; // Will try to use as much space as possible and will float to share space evenly with other floaters.
+ (instancetype)buttonSpacer;

+ (instancetype)formItemWithDingbat:(NSString *)dingbat;
+ (instancetype)formItemWithLabel:(NSString *)label;
+ (instancetype)formItemWithLabel:(NSString *)label subTitle:(NSString *)subtitle;
+ (instancetype)formItemWithMultiLineLabel:(NSString *)label;

+ (instancetype)formItemArrow;

@end

@interface FormCustomViewItem (Helpers)

+ (instancetype)formCustomViewItemWithView:(UIView *)view;
+ (instancetype)formCustomViewItemWithView:(UIView *)view edgeInsets:(UIEdgeInsets)edgeInsets;

@end

@interface FormActionItem (Helpers)

+ (instancetype)formItemWithType:(FormItemType)itemType title:(NSString *)title action:(dispatch_block_t _Nullable)action;
+ (instancetype)formActionItemWithTitle:(NSString *)title action:(dispatch_block_t _Nullable)action;
+ (instancetype)formSecondaryItemWithTitle:(NSString *)title action:(dispatch_block_t _Nullable)action;
+ (instancetype)formDestrutiveItemWithTitle:(NSString *)title action:(dispatch_block_t _Nullable)action;



@end

NS_ASSUME_NONNULL_END
