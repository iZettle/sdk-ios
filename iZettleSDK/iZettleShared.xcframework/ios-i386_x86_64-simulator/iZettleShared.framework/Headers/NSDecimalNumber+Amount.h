//
//  NSDecimalNumber+Amount.h
//  iZettleShared
//
//  Created by Jens Utbult on 2014-09-23.
//  Copyright (c) 2014 iZettle. All rights reserved.
//

@import Foundation;

/**
 
 The NSDecimalNumber+Amount category helps with the problem that the defaultBehavior property on 
 NSDecimalNumber is set per thread and not globally. It also solves the problem of our SDK
 sometimes overriding the default behavior of the client implementation on completion.
 
*/

@interface NSDecimalNumber (Amount)

/// TODO: This behaviour should not be global but should instead depend on the account. In the future we will encapsulate this in a Money value type that also carries around it's currency and behaviour, but we would like to wait until more code is converted to swift.
/// Returns the default amount behavior.
+ (NSDecimalNumberHandler *)amountDefaultBehavior;

/// Addition using the amountDefaultBehavior.
- (NSDecimalNumber *)amountDecimalNumberByAdding:(NSDecimalNumber *)decimalNumber;
/// Subtracion using the amountDefaultBehavior.
- (NSDecimalNumber *)amountDecimalNumberBySubtracting:(NSDecimalNumber *)decimalNumber;
/// Multiplication using the amountDefaultBehavior.
- (NSDecimalNumber *)amountDecimalNumberByMultiplyingBy:(NSDecimalNumber *)decimalNumber;
/// Division using the amountDefaultBehavior.
- (NSDecimalNumber *)amountDecimalNumberByDividingBy:(NSDecimalNumber *)decimalNumber;
/// Raising to power using the amountDefaultBehavior.
- (NSDecimalNumber *)amountDecimalNumberByRaisingToPower:(NSUInteger)power;
/// Multiplying by power of 10 using the amountDefaultBehavior.
- (NSDecimalNumber *)amountDecimalNumberByMultiplyingByPowerOf10:(short)power;
/// Returns the absolute value of a decimal number
- (NSDecimalNumber *)abs;
/// Returns the NSDecimalNumber multiplied with -1
- (NSDecimalNumber *)invert;

@end
