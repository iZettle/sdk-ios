//
//  NumericKeyboard.h
//  iZettle
//
//  Created by Måns Bernhardt on 2011-09-01.
//  Copyright 2011 iZettle AB. All rights reserved.
//

@import UIKit;
#import "NumericKeypad.h"

extern NSString *const NumericKeyboardDebugKey;

enum { // extends UIKeyboardType (UITextInputTraits.h)
    KeyboadTypeNumberPad  = 1000, // Numeric keypad with no decimal separator
    KeyboadTypeDecimalPad = 2000, // Numeric keypad with decimal separator
};

/*
 To use a numeric keypad, set the textfield's inputView to [NumericKeyboard shared] and [NumericKeyboard shared].delgate to the textField.
 The keyboard is using a NumericKeypad to layout the buttons.
 
 */


@interface NumericKeyboard : UIView

+ (NumericKeyboard *)shared;

@property (nonatomic, weak) id<UIKeyInput> delegate;

@property (readwrite, nonatomic) BOOL nextButtonEnabled;

@property (readonly, nonatomic) NumericKeypad *keypad;
@property (readonly, nonatomic) NumericKeypad *detachedKeypad;

/// Returns the current numeric keyboard if present otherwise nil.
+ (NumericKeyboard *)currentNumericKeyboard;

@end


/*
 If the delegate responds to detachedKeypad, the keyboard's pad will copy that keypad's style and position it's keypad to align with the deteche keyboard.
 UITextFields as a convenince method automaticallyTryToFindDetachedKeypad, that will automatically return the closest ancester keypad.
*/

@interface NSObject (DetachedKeypad)

@property (nonatomic, readonly) NumericKeypad *detachedKeypad;

@end


@interface NumericKeypad (DetachedKeypad)

- (BOOL)shouldDismissKeyboardWhenClickedOutsideKeypad; // optinally implement and return true to dismiss keyboard (resign first reponder on delegate) if tappted outside keypad.

@end

// Different styles (not layouts) of keyboards.

@interface NumericKeypadBase : NumericKeypad

- (CGFloat)numberFontSize;
- (CGFloat)dingbatFontSize;
- (CGFloat)textFontSize;
- (UIColor*)lineColor;

- (void)styleButton:(UIButton *)button forKey:(NumericKeypadKey)key;

@end


@interface NumericKeypadPad : NumericKeypadBase

@end

@interface NumericKeypadPhone : NumericKeypadBase

@end

