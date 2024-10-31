// Copyright © 2024 PayPal Inc. All rights reserved.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// Manual Card Entry error domain.
extern NSErrorDomain const IZSDKManualCardEntryErrorDomain;

/// Defines Manual Card Entry SDK errors.
typedef NS_ERROR_ENUM(IZSDKManualCardEntryErrorDomain, IZSDKManualCardEntryErrorCode) {

    // Common errors
    IZSDKManualCardEntryNetworkError               = -3000,
    IZSDKManualCardEntryTechnicalError             = -3001,

    // Payment errors
    IZSDKManualCardEntryLocationFailed             = -3101,
    IZSDKManualCardEntryFeatureNotEnabled          = -3102,
    IZSDKManualCardEntrySellerDataError            = -3104,
    IZSDKManualCardEntryPaymentCancelledByMerchant = -3105,
    IZSDKManualCardEntryInvalidAmount              = -3108,
    IZSDKManualCardEntryAmountBelowMinimum         = -3109,
    IZSDKManualCardEntryAmountAboveMaximum         = -3110,

    // PaymentInfoErrors
    IZSDKManualCardEntryNotFound                   = -3201,
    IZSDKManualCardEntryNotAuthorized              = -3202,
    IZSDKManualCardEntryRetrievalCancelled         = -3203,

    // Refund errors
    IZSDKManualCardEntryRefundAmountTooHigh        = -3301,
    IZSDKManualCardEntryRefundInsufficientFunds    = -3302,
    IZSDKManualCardEntryRefundFailed               = -3303,
    IZSDKManualCardEntryRefundCancelled            = -3304
};

@interface IZSDKManualCardEntryPaymentInfo: NSObject

/// Total transaction amount.
@property (nonatomic, readonly) NSDecimalNumber *amount;

/// Zettle's reference to the payment that should be displayed on receipts (not to be confused with the reference provided by you during a charge or refund operation).
@property (nonatomic, readonly) NSString *referenceNumber;

/// The Zettle transaction identifier for the transaction itself.
@property (nonatomic, readonly) NSString *transactionId;

@end

NS_ASSUME_NONNULL_END
