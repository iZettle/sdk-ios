//
//  Skinner.h
//  iZettle
//
//  Created by Mattias Jähnke on 2013-04-25.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import UIKit;
#import "UIDevice+Utilities.h"

#define NORMAL_FONT_SIZE ([UIDevice isCurrentlyRegularSized] ? 18 : 17)
#define SMALL_FONT_SIZE ([UIDevice isCurrentlyRegularSized] ? 14 : 14)
#define MINI_FONT_SIZE 14
#define INPUT_FONT_SIZE ([UIDevice isCurrentlyRegularSized] ? 18 : 17)

#define BUTTON_FONT_SIZE ([UIDevice isCurrentlyRegularSized] ? 20 : 19)
#define SMALL_BUTTON_FONT_SIZE ([UIDevice isCurrentlyRegularSized] ? 17 : 16)
#define ROUNDED_BUTTON_FONT_SIZE ([UIDevice isCurrentlyRegularSized] ? 15 : 13)
#define LARGE_AMOUNT_FONT_SIZE ([UIDevice isCurrentlyRegularSized] ? 49 : [UIDevice isCurrentlyCompactAndTallSized] ? 45 : 42)

#define DINGBAT_DEFAULT_FONT_SIZE 26

#define NAVIGATION_BAR_HEIGHT ([UIDevice isCurrentlyRegularSized] ? 70 : 64)
#define IPAD_MODAL_NAVIGATION_BAR_HEIGHT 64


@interface IZTheme : NSObject

+ (void)applyApplicationTheme;

@end

@interface UIColor(LocalPresets)

+ (UIColor *)lightBorderColor;
+ (UIColor *)menuBorderColor;
+ (UIColor *)backLayerColor;

@end
