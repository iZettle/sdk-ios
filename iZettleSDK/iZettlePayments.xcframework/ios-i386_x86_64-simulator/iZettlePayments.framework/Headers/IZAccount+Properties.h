//
//  IZAccount+Properties.h
//  iZettleStorePurchase
//
//  Created by Mattias Jähnke on 2015-05-26.
//  Copyright (c) 2015 iZettle. All rights reserved.
//

#import "IZCardReader.h"
#import "IZAccount.h"
@import Foundation;

NS_ASSUME_NONNULL_BEGIN

@class CashDenominations, IZCardReaderViewModel;

@interface IZAccount (Properties)

@property(readonly) NSString *userName NS_REFINED_FOR_SWIFT;
@property(readonly) NSString *userFullName NS_REFINED_FOR_SWIFT; // Subaccount only?
@property(readonly) NSString *userEmail NS_REFINED_FOR_SWIFT;
@property(readonly) NSString *organizationName NS_REFINED_FOR_SWIFT;
@property(readonly) NSString *organizationUUID NS_REFINED_FOR_SWIFT;
@property(readonly) NSTimeZone *userTimeZone NS_REFINED_FOR_SWIFT;
@property(readonly) int64_t userID NS_REFINED_FOR_SWIFT;
@property(readonly) NSString *userCountryCode NS_REFINED_FOR_SWIFT;
@property(readonly) NSString *countryCallingCode NS_REFINED_FOR_SWIFT;
@property(readonly) BOOL isCompany NS_REFINED_FOR_SWIFT;

/**
 Returns identifiers of supported card readers
 */
@property(readonly) NSArray<NSString *> *supportedReaders;
- (BOOL)supportsV2Reader;

@property(readonly) NSArray<NSString *> *deprecatedReaders;

- (IZFuture<UIImage *> *)profileImage NS_REFINED_FOR_SWIFT; // Temp objc backward compatible for SDK code relying on the URL session cashe and always fetching image of size medium web

@property(readonly) BOOL isCashRegister NS_REFINED_FOR_SWIFT;

@property(readonly) BOOL isLoyaltyEnabled;
@property(readonly) BOOL isInvoiceActivated NS_REFINED_FOR_SWIFT;

@property(readonly) IZCurrency *currency NS_REFINED_FOR_SWIFT;
@property(readonly) NSDictionary *transactionConfigurationForCurrentCurrency;
@property(readonly) NSNumberFormatter *currencyFormatter;

@property(readonly) NSInteger maxAmountDigits;

@property(readonly) NSTimeInterval paymentSessionMaxIdleTime;

@property(readonly) BOOL needsPhotoVerification NS_REFINED_FOR_SWIFT;

- (NSDictionary *)paymentInfoForCurrentCurrencyAndInterface:(CardInterface)cardInterface;
- (NSDecimalNumber *)minimumAmountForCardInterface:(CardInterface)cardInterface;
- (NSDecimalNumber *)maximumAmountForCardInterface:(CardInterface)cardInterface;

- (NSDecimalNumber *)maximumAmountForInvoice;
- (NSDecimalNumber *)minimumAmountForInvoice;

- (BOOL)textkeyIsTranslatedInUserCountry:(NSString *)textKey;

- (BOOL)isFeatureLockedWithId:(NSString *)lockId NS_REFINED_FOR_SWIFT;;

@property (nonatomic, readonly, nullable) NSString *supportPhoneNumber;
@property (nonatomic, readonly) NSString *supportEmailAddress;

// Card reader config
@property (nonatomic, readonly) NSArray<NSNumber *> *instalmentOptions;
@property (nonatomic, readonly) NSDecimalNumber *minimumInstalmentAmount;
@property (nonatomic, readonly) BOOL useAccountTypeSelection;

@end


@interface IZAccount (AccountConfiguration)

- (NSCalendar *)calendarWithAccountTimeZone;

@end

@interface NSDecimalNumber (Session)

- (NSString *)stringWithCurrency:(IZCurrency *)currency;
- (NSString *)stringWithSmartDecimalsAndCurrency:(IZCurrency *)currency; // Remove decimals if decimals equals ,00

@end


NS_ASSUME_NONNULL_END
