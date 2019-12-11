//
//  Copyright (c) 2019 iZettle. All rights reserved.
//

@import UIKit;

NS_ASSUME_NONNULL_BEGIN

@protocol IZColorThemeProvider <NSObject>

@property (nonatomic, assign, readonly) UIColor *actionDestructiveBackgroundDefault;
@property (nonatomic, assign, readonly) UIColor *actionDestructiveBackgroundDisabled;
@property (nonatomic, assign, readonly) UIColor *actionDestructiveBackgroundHover;
@property (nonatomic, assign, readonly) UIColor *actionDestructiveBackgroundSelected;
@property (nonatomic, assign, readonly) UIColor *actionDestructiveBorderDefault;
@property (nonatomic, assign, readonly) UIColor *actionDestructiveBorderDisabled;
@property (nonatomic, assign, readonly) UIColor *actionDestructiveBorderHover;
@property (nonatomic, assign, readonly) UIColor *actionDestructiveBorderSelected;
@property (nonatomic, assign, readonly) UIColor *actionDestructiveTextDefault;
@property (nonatomic, assign, readonly) UIColor *actionDestructiveTextDisabled;
@property (nonatomic, assign, readonly) UIColor *actionDestructiveTextHover;
@property (nonatomic, assign, readonly) UIColor *actionDestructiveTextSelected;
@property (nonatomic, assign, readonly) UIColor *actionInlineBackgroundDefault;
@property (nonatomic, assign, readonly) UIColor *actionInlineBackgroundDisabled;
@property (nonatomic, assign, readonly) UIColor *actionInlineBackgroundHover;
@property (nonatomic, assign, readonly) UIColor *actionInlineBackgroundSelected;
@property (nonatomic, assign, readonly) UIColor *actionInlineBorderDefault;
@property (nonatomic, assign, readonly) UIColor *actionInlineBorderDisabled;
@property (nonatomic, assign, readonly) UIColor *actionInlineBorderHover;
@property (nonatomic, assign, readonly) UIColor *actionInlineBorderSelected;
@property (nonatomic, assign, readonly) UIColor *actionInlineDestructiveBackgroundDefault;
@property (nonatomic, assign, readonly) UIColor *actionInlineDestructiveBackgroundDisabled;
@property (nonatomic, assign, readonly) UIColor *actionInlineDestructiveBackgroundHover;
@property (nonatomic, assign, readonly) UIColor *actionInlineDestructiveBackgroundSelected;
@property (nonatomic, assign, readonly) UIColor *actionInlineDestructiveBorderDefault;
@property (nonatomic, assign, readonly) UIColor *actionInlineDestructiveBorderDisabled;
@property (nonatomic, assign, readonly) UIColor *actionInlineDestructiveBorderHover;
@property (nonatomic, assign, readonly) UIColor *actionInlineDestructiveBorderSelected;
@property (nonatomic, assign, readonly) UIColor *actionInlineDestructiveTextDefault;
@property (nonatomic, assign, readonly) UIColor *actionInlineDestructiveTextDisabled;
@property (nonatomic, assign, readonly) UIColor *actionInlineDestructiveTextHover;
@property (nonatomic, assign, readonly) UIColor *actionInlineDestructiveTextSelected;
@property (nonatomic, assign, readonly) UIColor *actionInlineTextDefault;
@property (nonatomic, assign, readonly) UIColor *actionInlineTextDisabled;
@property (nonatomic, assign, readonly) UIColor *actionInlineTextHover;
@property (nonatomic, assign, readonly) UIColor *actionInlineTextSelected;
@property (nonatomic, assign, readonly) UIColor *actionMinorBackgroundDefault;
@property (nonatomic, assign, readonly) UIColor *actionMinorBackgroundDisabled;
@property (nonatomic, assign, readonly) UIColor *actionMinorBackgroundHover;
@property (nonatomic, assign, readonly) UIColor *actionMinorBackgroundSelected;
@property (nonatomic, assign, readonly) UIColor *actionMinorBorderDefault;
@property (nonatomic, assign, readonly) UIColor *actionMinorBorderDisabled;
@property (nonatomic, assign, readonly) UIColor *actionMinorBorderHover;
@property (nonatomic, assign, readonly) UIColor *actionMinorBorderSelected;
@property (nonatomic, assign, readonly) UIColor *actionMinorTextDefault;
@property (nonatomic, assign, readonly) UIColor *actionMinorTextDisabled;
@property (nonatomic, assign, readonly) UIColor *actionMinorTextHover;
@property (nonatomic, assign, readonly) UIColor *actionMinorTextSelected;
@property (nonatomic, assign, readonly) UIColor *actionPrimaryBackgroundDefault;
@property (nonatomic, assign, readonly) UIColor *actionPrimaryBackgroundDisabled;
@property (nonatomic, assign, readonly) UIColor *actionPrimaryBackgroundHover;
@property (nonatomic, assign, readonly) UIColor *actionPrimaryBackgroundSelected;
@property (nonatomic, assign, readonly) UIColor *actionPrimaryBorderDefault;
@property (nonatomic, assign, readonly) UIColor *actionPrimaryBorderDisabled;
@property (nonatomic, assign, readonly) UIColor *actionPrimaryBorderHover;
@property (nonatomic, assign, readonly) UIColor *actionPrimaryBorderSelected;
@property (nonatomic, assign, readonly) UIColor *actionPrimaryTextDefault;
@property (nonatomic, assign, readonly) UIColor *actionPrimaryTextDisabled;
@property (nonatomic, assign, readonly) UIColor *actionPrimaryTextHover;
@property (nonatomic, assign, readonly) UIColor *actionPrimaryTextSelected;
@property (nonatomic, assign, readonly) UIColor *actionSecondaryBackgroundDefault;
@property (nonatomic, assign, readonly) UIColor *actionSecondaryBackgroundDisabled;
@property (nonatomic, assign, readonly) UIColor *actionSecondaryBackgroundHover;
@property (nonatomic, assign, readonly) UIColor *actionSecondaryBackgroundSelected;
@property (nonatomic, assign, readonly) UIColor *actionSecondaryBorderDefault;
@property (nonatomic, assign, readonly) UIColor *actionSecondaryBorderDisabled;
@property (nonatomic, assign, readonly) UIColor *actionSecondaryBorderHover;
@property (nonatomic, assign, readonly) UIColor *actionSecondaryBorderSelected;
@property (nonatomic, assign, readonly) UIColor *actionSecondaryTextDefault;
@property (nonatomic, assign, readonly) UIColor *actionSecondaryTextDisabled;
@property (nonatomic, assign, readonly) UIColor *actionSecondaryTextHover;
@property (nonatomic, assign, readonly) UIColor *actionSecondaryTextSelected;
@property (nonatomic, assign, readonly) UIColor *backgroundDefault;
@property (nonatomic, assign, readonly) UIColor *backgroundError;
@property (nonatomic, assign, readonly) UIColor *backgroundGroupedPrimary;
@property (nonatomic, assign, readonly) UIColor *backgroundGroupedSecondary;
@property (nonatomic, assign, readonly) UIColor *backgroundHighlight;
@property (nonatomic, assign, readonly) UIColor *backgroundInfo;
@property (nonatomic, assign, readonly) UIColor *backgroundInverted;
@property (nonatomic, assign, readonly) UIColor *backgroundPlaceholder;
@property (nonatomic, assign, readonly) UIColor *backgroundSuccess;
@property (nonatomic, assign, readonly) UIColor *backgroundWarning;
@property (nonatomic, assign, readonly) UIColor *brandLilac;
@property (nonatomic, assign, readonly) UIColor *brandMagnetic;
@property (nonatomic, assign, readonly) UIColor *brandMint;
@property (nonatomic, assign, readonly) UIColor *brandSalmon;
@property (nonatomic, assign, readonly) UIColor *brandSilicon;
@property (nonatomic, assign, readonly) UIColor *dividerAction;
@property (nonatomic, assign, readonly) UIColor *dividerDefault;
@property (nonatomic, assign, readonly) UIColor *dividerError;
@property (nonatomic, assign, readonly) UIColor *dividerFocus;
@property (nonatomic, assign, readonly) UIColor *dividerInfo;
@property (nonatomic, assign, readonly) UIColor *dividerSuccess;
@property (nonatomic, assign, readonly) UIColor *dividerWarning;
@property (nonatomic, assign, readonly) UIColor *iconAction;
@property (nonatomic, assign, readonly) UIColor *iconDefault;
@property (nonatomic, assign, readonly) UIColor *iconDisabled;
@property (nonatomic, assign, readonly) UIColor *iconErrorLarge;
@property (nonatomic, assign, readonly) UIColor *iconErrorSmall;
@property (nonatomic, assign, readonly) UIColor *iconHighlight;
@property (nonatomic, assign, readonly) UIColor *iconInfo;
@property (nonatomic, assign, readonly) UIColor *iconInverted;
@property (nonatomic, assign, readonly) UIColor *iconSecondary;
@property (nonatomic, assign, readonly) UIColor *iconSuccessLarge;
@property (nonatomic, assign, readonly) UIColor *iconSuccessSmall;
@property (nonatomic, assign, readonly) UIColor *iconWarningLarge;
@property (nonatomic, assign, readonly) UIColor *iconWarningSmall;
@property (nonatomic, assign, readonly) UIColor *textDefault;
@property (nonatomic, assign, readonly) UIColor *textDisabled;
@property (nonatomic, assign, readonly) UIColor *textError;
@property (nonatomic, assign, readonly) UIColor *textHighlight;
@property (nonatomic, assign, readonly) UIColor *textInfo;
@property (nonatomic, assign, readonly) UIColor *textInverted;
@property (nonatomic, assign, readonly) UIColor *textPlaceholder;
@property (nonatomic, assign, readonly) UIColor *textSecondary;
@property (nonatomic, assign, readonly) UIColor *textSuccess;
@property (nonatomic, assign, readonly) UIColor *textWarning;

@end

NS_ASSUME_NONNULL_END
