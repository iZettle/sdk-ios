//
//  TextFieldHandler.h
//  TextFieldTest
//
//  Created by Måns Bernhardt on 2011-10-11.
//  Copyright (c) 2011 Bit of Mind AB. All rights reserved.
//

@import UIKit;

typedef BOOL (^CheckStringBlock)(NSString *text);

@class NumericKeypad;

@interface TextFieldHandler : NSObject<UITextFieldDelegate, UIKeyInput, NSCopying>

@property (copy, nonatomic) NSAttributedString* (^textFieldAttributedStringHandler) (NSString*);

@property (nonatomic, strong) UIColor *validTextColor;
@property (nonatomic, strong) UIColor *invalidTextColor;

@property (nonatomic, weak) UITextField *textField;
@property (nonatomic, weak) id<UITextFieldDelegate> delegate;
@property (nonatomic, strong) TextFieldHandler *nextHandler;
@property (nonatomic, strong) TextFieldHandler *previousHandler;
@property (nonatomic, assign) NSUInteger maxCharacters;

@property (nonatomic, copy) NSString *text;

@property (nonatomic, copy) NSString *secureCharacter;
@property (nonatomic, assign) NSRange secureRange;
@property (nonatomic, copy) NSIndexSet *dividerPositions;
@property (nonatomic, copy) NSString *dividerString;

@property (nonatomic, copy) CheckStringBlock validBlock;
@property (nonatomic, copy) CheckStringBlock validInputBlock;
@property (nonatomic, readonly) BOOL isValid;

@property (nonatomic, strong) NumericKeypad *detachedKeypad;
@property (nonatomic, assign) BOOL automaticallyTryToFindDetachedKeypad; // if detachedKeypad is not set and automaticallyTryToFindDetachedKeypad is true, a closest (from textfield) ancester NumericKeypad view will be searched and set.


- (void)validate;


- (BOOL)isAllowedInputString:(NSString *)string;
- (BOOL)shouldJumpToNextForText:(NSString *)text;


- (void)copyPropertiesTo:(TextFieldHandler *)result;

@end

@interface AmountTextFieldHandler : TextFieldHandler

@property (nonatomic, strong) NSNumberFormatter *overridingFormatter;
@property (nonatomic, strong) NSNumberFormatter *formatter;
@property (nonatomic, strong) NSDecimalNumber *amount;
@property (nonatomic, assign) NSUInteger maxIntegerDigits;

@end

@interface NumberTextFieldHandler : TextFieldHandler

@property (nonatomic, strong) NSDecimalNumber *number;
@property (nonatomic, assign) NSUInteger maxIntegerDigits;
@property (nonatomic, readonly) BOOL decimalCharacterAllowed;

@end

@interface IntegerNumberTextFieldHandler : NumberTextFieldHandler

@end
