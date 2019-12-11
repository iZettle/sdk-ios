//
//  UITextField+TextHandler.h
//  TextFieldTest
//
//  Created by Måns Bernhardt on 2011-10-13.
//  Copyright (c) 2011 Bit of Mind AB. All rights reserved.
//

@import UIKit;
#import "TextFieldHandler.h"

@class TextFieldHandler, NumericKeypad;
extern NSString *const TextFieldUnderlyingTextDidChangeNotification;

@interface UITextField (TextHandler)

@property (nonatomic, readonly) BOOL isTextFieldHandlerInstalled;
@property (nonatomic, readonly) BOOL isAmountTextFieldHandlerInstalled;
@property (nonatomic, readonly) BOOL isNumberTextFieldHandlerInstalled;

@property (copy, nonatomic) NSAttributedString* (^textFieldAttributedStringHandler) (NSString*);

@property (nonatomic, assign) NSUInteger maxCharacters;
@property (nonatomic, copy) CheckStringBlock validBlock;
@property (nonatomic, copy) CheckStringBlock validInputBlock;
@property (nonatomic, readonly) BOOL isValid;

@property (nonatomic, copy) NSString *secureCharacter;
@property (nonatomic, assign) NSRange secureRange;
@property (nonatomic, copy) NSIndexSet *dividerPositions;
@property (nonatomic, copy) NSString *dividerString;
@property (nonatomic, copy) NSString *underlyingText;

@property (nonatomic, assign) UIColor *validTextColor;
@property (nonatomic, assign) UIColor *invalidTextColor;

@property (nonatomic, assign) id<UITextFieldDelegate> handlerDelegate;

@property (nonatomic, strong) IBOutlet NumericKeypad *detachedKeypad;
@property (nonatomic, assign) BOOL automaticallyTryToFindDetachedKeypad; // if detachedKeypad is not set and automaticallyTryToFindDetachedKeypad is true, a closest (from textfield) ancester NumericKeypad view will be searched and set.


- (void)validate;

- (void)clearFieldsInChain;
- (void)becomeFirstResponderInChain; // set first responder to first empty field or last field

+ (CheckStringBlock)numericValidInputBlock;
+ (CheckStringBlock)decimalNumericValidInputBlock;
+ (void)chainTextFields:(UITextField *)firstArg, ...;
+ (void)chainTextFieldsInArray:(NSArray *)textFields;

@end

@class IZCurrency;

@interface UITextField (AmountTextHandler)

@property (nonatomic, strong) NSNumberFormatter *formatter;
@property (nonatomic, strong) NSDecimalNumber *amount;
@property (nonatomic, assign) NSUInteger maxIntegerDigits;
@property (nonatomic, strong) NSNumberFormatter *overridingFormatter;

- (void)setupAmountFieldWithFormatter:(NSNumberFormatter*)formatter maxIntegerDigits:(NSUInteger)maxDigits placeHolder:(NSString*)placeHolder;
- (void)setupAmountField;

@end


@interface UITextField (NumberTextHandler)

@property (nonatomic, strong) NSDecimalNumber *number;
@property (nonatomic, assign) NSUInteger maxNumberIntegerDigits;
- (void)setupNumberField;

@end

@interface UITextField (IntegerNumberTextHandler)

- (void)setupIntegerNumberField;

@end