//
//  UIColor+Presets.h
//  iZettle
//
//  Created by Nino Höglund on 2012-04-01.
//  Copyright (c) 2012 iZettle. All rights reserved.
//

@import UIKit;

NS_ASSUME_NONNULL_BEGIN

//RGB color macro
#define UIColorFromRGB(rgbValue) [UIColor \
colorWithRed:((float)((rgbValue & 0xFF0000) >> 16))/255.0 \
green:((float)((rgbValue & 0xFF00) >> 8))/255.0 \
blue:((float)(rgbValue & 0xFF))/255.0 alpha:1.0]

//RGB color macro with alpha
#define UIColorFromRGBWithAlpha(rgbValue,a) [UIColor \
colorWithRed:((float)((rgbValue & 0xFF0000) >> 16))/255.0 \
green:((float)((rgbValue & 0xFF00) >> 8))/255.0 \
blue:((float)(rgbValue & 0xFF))/255.0 alpha:a]

#define RGB(r, g, b) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1]
//#define RGBA(r, g, b, a) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:a]

@interface UIColor (Helpers)

+ (UIColor *)randomColor;

// Helpers for converting from Photoshop/Finder standard HSB values.
// (H)ue = 0-360 degrees, (S)aturation = 0-100%, (B)rightness = 0-100%
+ (UIColor*)colorWithH:(CGFloat)h S:(CGFloat)s B:(CGFloat)b A:(CGFloat)a;
+ (UIColor*)colorWithH:(CGFloat)h S:(CGFloat)s B:(CGFloat)b;

@end

@interface UIColor (Proxy)

+ (UIColor *)iz_actionDestructiveBackgroundDefault;
+ (UIColor *)iz_actionDestructiveBackgroundDisabled;
+ (UIColor *)iz_actionDestructiveBackgroundHover;
+ (UIColor *)iz_actionDestructiveBackgroundSelected;
+ (UIColor *)iz_actionDestructiveBorderDefault;
+ (UIColor *)iz_actionDestructiveBorderDisabled;
+ (UIColor *)iz_actionDestructiveBorderHover;
+ (UIColor *)iz_actionDestructiveBorderSelected;
+ (UIColor *)iz_actionDestructiveTextDefault;
+ (UIColor *)iz_actionDestructiveTextDisabled;
+ (UIColor *)iz_actionDestructiveTextHover;
+ (UIColor *)iz_actionDestructiveTextSelected;
+ (UIColor *)iz_actionInlineBackgroundDefault;
+ (UIColor *)iz_actionInlineBackgroundDisabled;
+ (UIColor *)iz_actionInlineBackgroundHover;
+ (UIColor *)iz_actionInlineBackgroundSelected;
+ (UIColor *)iz_actionInlineBorderDefault;
+ (UIColor *)iz_actionInlineBorderDisabled;
+ (UIColor *)iz_actionInlineBorderHover;
+ (UIColor *)iz_actionInlineBorderSelected;
+ (UIColor *)iz_actionInlineDestructiveBackgroundDefault;
+ (UIColor *)iz_actionInlineDestructiveBackgroundDisabled;
+ (UIColor *)iz_actionInlineDestructiveBackgroundHover;
+ (UIColor *)iz_actionInlineDestructiveBackgroundSelected;
+ (UIColor *)iz_actionInlineDestructiveBorderDefault;
+ (UIColor *)iz_actionInlineDestructiveBorderDisabled;
+ (UIColor *)iz_actionInlineDestructiveBorderHover;
+ (UIColor *)iz_actionInlineDestructiveBorderSelected;
+ (UIColor *)iz_actionInlineDestructiveTextDefault;
+ (UIColor *)iz_actionInlineDestructiveTextDisabled;
+ (UIColor *)iz_actionInlineDestructiveTextHover;
+ (UIColor *)iz_actionInlineDestructiveTextSelected;
+ (UIColor *)iz_actionInlineTextDefault;
+ (UIColor *)iz_actionInlineTextDisabled;
+ (UIColor *)iz_actionInlineTextHover;
+ (UIColor *)iz_actionInlineTextSelected;
+ (UIColor *)iz_actionMinorBackgroundDefault;
+ (UIColor *)iz_actionMinorBackgroundDisabled;
+ (UIColor *)iz_actionMinorBackgroundHover;
+ (UIColor *)iz_actionMinorBackgroundSelected;
+ (UIColor *)iz_actionMinorBorderDefault;
+ (UIColor *)iz_actionMinorBorderDisabled;
+ (UIColor *)iz_actionMinorBorderHover;
+ (UIColor *)iz_actionMinorBorderSelected;
+ (UIColor *)iz_actionMinorTextDefault;
+ (UIColor *)iz_actionMinorTextDisabled;
+ (UIColor *)iz_actionMinorTextHover;
+ (UIColor *)iz_actionMinorTextSelected;
+ (UIColor *)iz_actionPrimaryBackgroundDefault;
+ (UIColor *)iz_actionPrimaryBackgroundDisabled;
+ (UIColor *)iz_actionPrimaryBackgroundHover;
+ (UIColor *)iz_actionPrimaryBackgroundSelected;
+ (UIColor *)iz_actionPrimaryBorderDefault;
+ (UIColor *)iz_actionPrimaryBorderDisabled;
+ (UIColor *)iz_actionPrimaryBorderHover;
+ (UIColor *)iz_actionPrimaryBorderSelected;
+ (UIColor *)iz_actionPrimaryTextDefault;
+ (UIColor *)iz_actionPrimaryTextDisabled;
+ (UIColor *)iz_actionPrimaryTextHover;
+ (UIColor *)iz_actionPrimaryTextSelected;
+ (UIColor *)iz_actionSecondaryBackgroundDefault;
+ (UIColor *)iz_actionSecondaryBackgroundDisabled;
+ (UIColor *)iz_actionSecondaryBackgroundHover;
+ (UIColor *)iz_actionSecondaryBackgroundSelected;
+ (UIColor *)iz_actionSecondaryBorderDefault;
+ (UIColor *)iz_actionSecondaryBorderDisabled;
+ (UIColor *)iz_actionSecondaryBorderHover;
+ (UIColor *)iz_actionSecondaryBorderSelected;
+ (UIColor *)iz_actionSecondaryTextDefault;
+ (UIColor *)iz_actionSecondaryTextDisabled;
+ (UIColor *)iz_actionSecondaryTextHover;
+ (UIColor *)iz_actionSecondaryTextSelected;
+ (UIColor *)iz_backgroundDefault;
+ (UIColor *)iz_backgroundError;
+ (UIColor *)iz_backgroundGroupedPrimary;
+ (UIColor *)iz_backgroundGroupedSecondary;
+ (UIColor *)iz_backgroundHighlight;
+ (UIColor *)iz_backgroundInfo;
+ (UIColor *)iz_backgroundInverted;
+ (UIColor *)iz_backgroundPlaceholder;
+ (UIColor *)iz_backgroundSuccess;
+ (UIColor *)iz_backgroundWarning;
+ (UIColor *)iz_brandLilac;
+ (UIColor *)iz_brandMagnetic;
+ (UIColor *)iz_brandMint;
+ (UIColor *)iz_brandSalmon;
+ (UIColor *)iz_brandSilicon;
+ (UIColor *)iz_dividerAction;
+ (UIColor *)iz_dividerDefault;
+ (UIColor *)iz_dividerError;
+ (UIColor *)iz_dividerFocus;
+ (UIColor *)iz_dividerInfo;
+ (UIColor *)iz_dividerSuccess;
+ (UIColor *)iz_dividerWarning;
+ (UIColor *)iz_iconAction;
+ (UIColor *)iz_iconDefault;
+ (UIColor *)iz_iconDisabled;
+ (UIColor *)iz_iconErrorLarge;
+ (UIColor *)iz_iconErrorSmall;
+ (UIColor *)iz_iconHighlight;
+ (UIColor *)iz_iconInfo;
+ (UIColor *)iz_iconInverted;
+ (UIColor *)iz_iconSecondary;
+ (UIColor *)iz_iconSuccessLarge;
+ (UIColor *)iz_iconSuccessSmall;
+ (UIColor *)iz_iconWarningLarge;
+ (UIColor *)iz_iconWarningSmall;
+ (UIColor *)iz_textDefault;
+ (UIColor *)iz_textDisabled;
+ (UIColor *)iz_textError;
+ (UIColor *)iz_textHighlight;
+ (UIColor *)iz_textInfo;
+ (UIColor *)iz_textInverted;
+ (UIColor *)iz_textPlaceholder;
+ (UIColor *)iz_textSecondary;
+ (UIColor *)iz_textSuccess;
+ (UIColor *)iz_textWarning;

#pragma mark - Component Specific colors. Be wary.

+ (UIColor *)iz_backgroundThumbnail;
+ (UIColor *)iz_bannerErrorText;
+ (UIColor *)iz_bannerSuccessText;
+ (UIColor *)iz_placeholderImageBackground;
+ (UIColor *)iz_standardBarBackground;

@end

NS_ASSUME_NONNULL_END

