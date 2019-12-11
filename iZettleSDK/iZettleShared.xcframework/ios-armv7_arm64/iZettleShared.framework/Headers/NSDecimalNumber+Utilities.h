//
//  NSDecimalNumber+Utilities.h
//  iZettleShared
//
//  Created by Mattias Jähnke on 2015-05-27.
//  Copyright (c) 2015 iZettle. All rights reserved.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

@interface NSDecimalNumber (Utilities)

+ (NSDecimalNumber *)decimalNumberFromValue:(id)number;
- (NSDecimalNumber *)percentageFromBackendRepresentation;
- (NSDecimalNumber *)backendRepresentationFromPercentage;

- (BOOL)iz_isLessThan:(NSDecimalNumber *)decimalNumber NS_SWIFT_NAME(isLessThan(_:));
- (BOOL)iz_isGreaterThan:(NSDecimalNumber *)decimalNumber NS_SWIFT_NAME(isGreaterThan(_:));

@end

@interface NSDecimalNumberHandler (Behavior)

+ (NSDecimalNumberHandler *)percentageBehavior;

@end

NS_ASSUME_NONNULL_END
