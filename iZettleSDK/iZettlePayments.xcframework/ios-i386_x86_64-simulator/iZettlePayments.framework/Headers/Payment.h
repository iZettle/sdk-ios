//
//  Payment.h
//  iZettleStorePurchase
//
//  Created by Måns Bernhardt on 2014-10-01.
//  Copyright (c) 2014 iZettle. All rights reserved.
//

@import iZettleShared;
#import "IZCardReader.h"

NS_ASSUME_NONNULL_BEGIN
/*
typedef NS_ENUM(NSInteger, PaymentType) {
    PaymentTypeCardReaderChip,
    PaymentTypeCardReaderSwipe,
    PaymentTypeCardReaderContactLess,
};*/

/// Returns a human-readable string for a payment type.
/// Note: Used for logging purposes, not to display to the end user.
NSString *cardInterfaceDescription(CardInterface cardInterface);

extern NSString *const PaymentProgressValueKey;
extern NSString *const PaymentProgressValueDidChangeNotification;

extern NSString *const PaymentErrorDomain;

typedef NS_ERROR_ENUM(PaymentErrorDomain, PaymentErrorCode) {
    PaymentErrorCodeTechnicalError,
    PaymentErrorCodeCancelledByUser,
    PaymentErrorCodeTimeout,
    PaymentErrorCodeInvalidState,
    PaymentErrorCodeAppRestart,
    PaymentErrorCodeCardHasChip,
    PaymentErrorCodeDeclined,// will pass PaymentCardTitleKey, PaymentCardMessageKey, PaymentReaderDisplayMessageKey in error message
    PaymentErrorCodeRequiresSMSFlow_Deprecated, // Kept around to maintain error code values.
    PaymentErrorCodeCancelledByBackend, // the payment has been canceled by backend and app will not need to cancel it any more
    PaymentErrorCodeNotRefundable,
    PaymentErrorCodeAuthenticationFailed,
    PaymentErrorCodePaymentAlreadyInProgress,
    PaymentErrorCodeInvalidAmount,
    PaymentErrorCodeProgramaticallyAborted_Deprecated, // Kept to maintain error code integers.
    PaymentErrorCodeCashRegisterPaymentNotAllowed,
    PaymentErrorCodePaymentNotFound,
    PaymentErrorCodeRefundCancelledByUser,
    PaymentErrorCodeCurrencyMismatch,
    PaymentErrorCodeDeclinedSCA
};


@interface NSError (Payment)

+ (NSString * _Nullable)_paymentErrorTitleForCode:(PaymentErrorCode)code;
+ (NSString *)_paymentErrorMessageForCode:(PaymentErrorCode)code;

+ (NSError *)paymentErrorWithCode:(PaymentErrorCode)code userInfo:(NSDictionary * __nullable)info;
+ (NSError *)paymentErrorWithCode:(PaymentErrorCode)code;
+ (NSError *)paymentCancelledByUserError;

- (BOOL)isPaymentErrorWithCode:(PaymentErrorCode)code;
@property (nonatomic, readonly) BOOL isPaymentCancelledByUserError;

@end


@interface PreChargeInfo : NSObject

@property(readonly, copy) NSString *chipATR;

+ (instancetype)preChargeInfoFromPayload:(NSDictionary *)payload;

@end

@class PhoneNumberInfo;

@interface IZCardPaymentInfo : NSObject

@property(readonly, copy) NSDictionary *originalPayload;

@property(readonly, copy) NSDecimalNumber *amount;
@property(readonly, copy, nullable) NSDecimalNumber *gratuityAmount;
@property(readonly, copy) NSString *cardHolderName;
@property(readonly, copy) NSString *cardBrand;
@property(readonly, copy) NSString *panLastDigits;
@property(readonly, copy) NSString *maskedPan;
@property(readonly, copy) NSString *panHash;
@property(readonly, copy) NSString *entryMode;
@property(readonly, copy, nullable) NSString *TVR;
@property(readonly, copy, nullable) NSString *TSI;
@property(readonly, copy, nullable) NSString *AID;
@property(readonly, copy) NSString *applicationName;
@property(readonly, copy) NSString *authorizationCode;
@property(readonly, copy) NSString *paymentReferenceNumber;
@property(readonly) NSInteger numberOfInstallments;
@property(readonly, copy, nullable) NSDecimalNumber *installmentAmount;
@property(readonly, copy, nullable) NSString *suggestedEmail;
@property(readonly, copy, nullable) PhoneNumberInfo *suggestedPhoneNumberInfo;
@property(readonly, copy, nullable) NSString *mxFIID;
@property(readonly, copy, nullable) NSString *mxCardType;

@property(readonly, assign) IZCardReaderModel readerModel;
@property(readonly, copy, nullable) NSString *readerModelName;
@property(readonly, copy, nullable) NSString *readerLocalizedName;

@property(readonly, copy, nullable) NSString *purchaseAgreementBody;
@property(readonly, copy, nullable) NSString *purchaseAgreementTitle;
@property(readonly, copy, nullable) NSString *purchaseAgreementLinkText;

@property(readonly) BOOL signatureRequired;

@property(copy) NSString *cardPaymentUUID;

// Used to deserialize PS2-payload (upper case payload)
+ (instancetype)cardPaymentInfoFromPayload:(NSDictionary *)payload amount:(NSDecimalNumber *)amount cardReader:(IZCardReader * __nullable)cardReader;

// Used to deserialize camel case payload
+ (instancetype)cardPaymentInfoFromPaymentDetailsPayload:(NSDictionary *)payload;

@property(readonly) BOOL isChipPayment;

@end

@interface IZCardPaymentInfo (Utilities)

@property (readonly) CardIssuer *issuer;

- (NSDictionary *)externalPaymentInfo;
- (NSDictionary *)paymentInfo;

@end

@interface CardStatus (Utilities)

@property (readonly) ReaderOperationType preChargeOperation;

@end

NS_ASSUME_NONNULL_END
