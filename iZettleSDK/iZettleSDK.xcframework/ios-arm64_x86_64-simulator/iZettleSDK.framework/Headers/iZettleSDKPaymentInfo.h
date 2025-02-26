// Copyright © 2024 PayPal Inc. All rights reserved.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// SDK error domain.
extern NSErrorDomain const IZSDKErrorDomain;

/// Defines SDK errors.
typedef NS_ERROR_ENUM(IZSDKErrorDomain, IZSDKErrorCode) {
    IZSDKErrorCodeUserNotLoggedIn             = -1,
    IZSDKErrorCodePaymentNotFound             = -100,
    IZSDKErrorCodeReferenceTooLong            = -101,
    IZSDKErrorCodeReferenceIsNil              = -102,
    IZSDKErrorCodeOperationAlreadyInProgress  = -300,
    IZSDKErrorCodeInvalidAmount               = -400,
    IZSDKErrorCodeAmountTooLow                = -401,
    IZSDKErrorCodeAmountTooHigh               = -402,
    IZSDKErrorCodeDeviceNotSupported          = -403,
    IZSDKErrorCodeNotEligible                 = -404,
    IZSDKErrorCodeAccountNotLinked            = -405,
    IZSDKErrorCodeNoNetwork                   = -406,
    IZSDKErrorCodeUnableToPresentView         = -407
};

@interface iZettleSDKPaymentInfo : NSObject

/// Dictionary representation of the payment information.
@property (nonatomic, readonly) NSDictionary<NSString *, id> *dictionary;

/// Paid amount (including gratuityAmount).
@property (nonatomic, readonly) NSDecimalNumber *amount;
@property (nonatomic, readonly) NSString *transactionId;
/// The amount of gratuity paid.
@property (nonatomic, readonly, nullable) NSDecimalNumber *gratuityAmount;

/// iZettles reference to the payment.
@property (nonatomic, readonly) NSString *referenceNumber;
/// EMV, CONTACTLESS_EMV, MAGSTRIPE_CONTACTLESS, MAGSTRIPE etc.
@property (nonatomic, readonly) NSString *entryMode;
@property (nonatomic, readonly) NSString *authorizationCode;

/// **** **** **** 1111
@property (nonatomic, readonly) NSString *obfuscatedPan;
/// Hash sum of the plain pan.
@property (nonatomic, readonly) NSString *panHash;
@property (nonatomic, readonly) NSString *cardBrand;
@property (nonatomic, readonly, nullable) NSString *cardIssuingBank;

@property (nonatomic, readonly, nullable) NSString *AID;
@property (nonatomic, readonly, nullable) NSString *TSI;
@property (nonatomic, readonly, nullable) NSString *TVR;
@property (nonatomic, readonly, nullable) NSString *applicationName;

// Only used for certain markets
@property (nonatomic, readonly, nullable) NSNumber *numberOfInstallments;
@property (nonatomic, readonly, nullable) NSDecimalNumber *installmentAmount;

// Only used for Mexico
@property (nonatomic, readonly, nullable) NSString *mxFIID;
@property (nonatomic, readonly, nullable) NSString *mxCardType;

@end

NS_ASSUME_NONNULL_END
