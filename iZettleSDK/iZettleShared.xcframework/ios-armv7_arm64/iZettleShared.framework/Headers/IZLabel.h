//
//  AppearanceLabel.h
//  iZettle
//
//  Created by Mattias Jähnke on 2013-04-29.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import UIKit;

@interface IZLabel : UILabel

@property (nonatomic, strong) UIFont *appearanceFont UI_APPEARANCE_SELECTOR;
@property (nonatomic, strong) UIFont *boldFont UI_APPEARANCE_SELECTOR;

@property (nonatomic, assign) CGFloat fontSize;

+ (id)labelWithText:(NSString *)text;

@end

@interface SmallLabel : IZLabel
@end

@interface MiniLabel : IZLabel
@end

@interface AmountLabel : IZLabel
@property (nonatomic, assign) CGFloat kerning UI_APPEARANCE_SELECTOR;
@end

@interface PlainLargeAmountLabel : AmountLabel

@end

@interface LargeAmountLabel : PlainLargeAmountLabel
@end

// Dingbat labels, often unsed inside input fields and buttons
@interface DingbatLabel : IZLabel
@end

@interface BoldDingbatLabel : DingbatLabel
@end

// Used to the right in table view cells
@interface ValueLabel : IZLabel
@end

// Larger, bold text for headlines in status screens etc
@interface HeadlineLabel : IZLabel
@end

// Navigation bar titles and similar
@interface NavigationTitleLabel : IZLabel
@end

// Used in status views
@interface SubheadlineLabel : IZLabel
@end

// OCRA text on cards
@interface CardInfoLabel : IZLabel
@end

@interface UILabel  (layout)

- (CGFloat)heightWithWidth:(CGFloat)width;

@end