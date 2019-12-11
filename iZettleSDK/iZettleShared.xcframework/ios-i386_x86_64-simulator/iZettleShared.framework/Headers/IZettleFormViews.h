//
//  IZettleFormViews.h
//  iZettleShared
//
//  Created by Mattias Jähnke on 2014-10-30.
//  Copyright (c) 2014 iZettle. All rights reserved.
//

#import "FormItemView.h"
#import "IZLabel.h"
#import "IZTextField.h"
#import "IZButton.h"
#import "SeparatorView.h"
#import "FormItem.h"
#import "IZPicker.h"
#import "TitleValueView.h"

#define BUTTON_FORMROW_HEIGHT ([UIDevice isCurrentlyRegularSized] ? 70 : 55)

// Multiline labels used outside rounded form frames
@interface MultilineLabelFormView : FormItemView
@property (nonatomic, assign) UIEdgeInsets insets;
@property (nonatomic, strong) IZLabel *textLabel;
@end

@interface InputFieldFormView : FormItemView
+ (void)setAmountFieldFormatter:(NSNumberFormatter *)formatter maxIntegerDigits:(NSUInteger)maxIntegerDigits;
@property (nonatomic, strong) IZTextField *textField;
@end

// Normal labels used exessively in form item views
@interface LabelFormView : FormItemView
+ (LabelFormView *)labelFormViewWithText:(NSString *)text;
@property (nonatomic, strong) IZLabel *textLabel;
@end

@interface DingbatFormView : FormItemView
@property (nonatomic, strong) DingbatLabel *dingbatLabel;
@end

@interface ButtonFormView : FormItemView
@property (nonatomic, strong) IZButton *button;

// Helpers - used to style the button with userinfo in the form system
@property (nonatomic, readwrite) UIColor *buttonTitleColor;
@property (nonatomic, readwrite) UIColor *highlightedButtonTitleColor;
@property (nonatomic, readwrite) UIColor *disabledButtonTitleColor;
@end

@interface SelectFormView : FormItemView
@property (nonatomic, strong) IZPicker *picker;
@end

@interface SeparatorFormView : FormItemView
@property (nonatomic, assign) CGFloat verticalSpacing;
@property (nonatomic, strong) SeparatorView *contentSeparatorView;
@end

@interface SpacerFormView : FormItemView
@property (nonatomic, readwrite) CGSize size;
@end

@interface DetailsFormView : LabelFormView
+ (DetailsFormView *)detailsFormViewWithText:(NSString *)text;
@end

@interface SwitchFormView : FormItemView
@property (nonatomic, strong) UISwitch *formSwitch;
@end

@interface TitleValueFormView : FormItemView
@property (nonatomic, strong) TitleValueView *titleValueView;
@end

@interface TitleSubtitleFormView : TitleValueFormView
@end

@interface ImageFormView : FormItemView
@property (nonatomic, assign) UIEdgeInsets insets;
@property (nonatomic, strong) UIImageView *imageView;
@end

@interface PhotoCaptureFormView : InputFieldFormView
@property (nonatomic, strong) IZButton *cameraButton;
@property (nonatomic, readwrite) UIImage *image;
@property (nonatomic, strong) UIImageView *imageView;
@end

@interface CustomViewContainerView : FormItemView
@end
