//
//  CashDenominations.h
//  iZettle
//
//  Created by Måns Bernhardt on 2012-04-24.
//  Copyright (c) 2012 iZettle. All rights reserved.
//

@import Foundation;

@interface CashDenominations : NSObject

- (id)initWithDenomiations:(NSArray *)denominations minSuggestedDenominator:(NSDecimalNumber *)minDenominator;

- (NSDecimalNumber *)amountRoundedToSmallestDenomination:(NSDecimalNumber *)amount;
- (NSDecimalNumber *)amountRoundedToSmallestDenominationMinimumSmallest:(NSDecimalNumber *)amount;

- (NSArray *)denominatedAmountSuggestionsForAmount:(NSDecimalNumber *)amount maxSuggestionCount:(NSUInteger)maxSuggestionCount;
- (NSDecimalNumber *)minDenominationForAmount:(NSDecimalNumber *)amount;

@property (nonatomic, strong, readonly) NSArray *denominations;

@end



@interface NSDecimalNumber (CashDenominations)

- (NSDecimalNumber *)cashAmountForDenominations:(CashDenominations *)denominations;
- (NSDecimalNumber *)cashAmountRoundedToMinimumSmallestForDenominations:(CashDenominations *)denominations;
- (NSDecimalNumber *)cashAmountRoundedToMinimumSmallestIfNotZeroForDenominations:(CashDenominations *)denominations;

@end


@interface CashDenominations (Utilities)

- (NSDecimalNumber *)changeFromPaidAmount:(NSDecimalNumber *)paidAmount amount:(NSDecimalNumber *)amount;

@end