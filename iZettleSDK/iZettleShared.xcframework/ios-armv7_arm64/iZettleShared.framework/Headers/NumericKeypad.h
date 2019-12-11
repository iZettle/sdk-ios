//
//  NumericKeyPad.h
//  iZettleShared
//
//  Created by Måns Bernhardt on 2014-04-01.
//  Copyright (c) 2014 iZettle. All rights reserved.
//

@import UIKit;

enum { // extends UIReturnKeyType (UITextInputTraits.h)
    NumericKeyboardReturnKeyAdd = 3000, // Custom key with add title
    NumericKeyboardReturnKeyTick = 3001, // Dingbat tick mark
    NumericKeyboardReturnKeyNone = 9999, // Custom key that should hide return key
};

typedef NS_ENUM(NSUInteger, NumericKeypadKey) {
    NumericKeypadKey0 = 100,
    NumericKeypadKey1,
    NumericKeypadKey2,
    NumericKeypadKey3,
    NumericKeypadKey4,
    NumericKeypadKey5,
    NumericKeypadKey6,
    NumericKeypadKey7,
    NumericKeypadKey8,
    NumericKeypadKey9,
    NumericKeypadKey00,
    NumericKeypadKeyDecimalSeparator,
    NumericKeypadKeyReturn,
    NumericKeypadKeyDismiss,
    NumericKeypadKeyBackspace,
};

@interface NumericKeypad : UIView

- (void)sharedInit;

@property (nonatomic, assign) UIEdgeInsets edgeInsets;
@property (nonatomic, assign) CGFloat separatorWidth;

@property (nonatomic, assign) NSUInteger returnKeyType;
@property (nonatomic, assign) BOOL hasDismissKey;
@property (nonatomic, assign) BOOL hasDecimalSeparatorKey;
@property (nonatomic, assign) BOOL isWide; // four columns typically used on iPad.

@property (nonatomic, copy) void (^keyPressedBlock)(NumericKeypadKey key);
@property (nonatomic, copy) void (^styleKeyBlock)(NumericKeypadKey key, UIButton *button);

- (void)recreateButtons;
- (void)restyleButtons;
- (void)retitleButtons;

- (UIButton *)buttonForKey:(NumericKeypadKey)key;


@end



