// Copyright © 2024 PayPal Inc. All rights reserved.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// PayPal QRC error domain.
extern NSErrorDomain const IZSDKPayPalQRCErrorDomain;

/// Defines PayPal QRC SDK errors.
typedef NS_ERROR_ENUM(IZSDKPayPalQRCErrorDomain, IZSDKPayPalQRCErrorCode) {

    // Common errors
    IZSDKPayPalQRCNetworkError               = -2000,
    IZSDKPayPalQRCTechnicalError             = -2001,

    // Payment errors
    IZSDKPayPalQRCLocationFailed             = -2101,
    IZSDKPayPalQRCFeatureNotEnabled          = -2102,
    IZSDKPayPalQRCOnboardingNotCompleted     = -2103,
    IZSDKPayPalQRCSellerDataError            = -2104,
    IZSDKPayPalQRCPaymentCancelledByMerchant = -2105,
    IZSDKPayPalQRCPaymentCancelledByBuyer    = -2106,
    IZSDKPayPalQRCPaymentTimeout             = -2107,
    IZSDKPayPalQRCInvalidAmount              = -2108,
    IZSDKPayPalQRCAmountBelowMinimum         = -2109,
    IZSDKPayPalQRCAmountAboveMaximum         = -2110,

    // PaymentInfoErrors
    IZSDKPayPalQRCNotFound                   = -2201,
    IZSDKPayPalQRCNotAuthorized              = -2202,
    IZSDKPayPalQRCRetrievalCancelled         = -2203,

    // Refund errors
    IZSDKPayPalQRCRefundAmountTooHigh        = -2301,
    IZSDKPayPalQRCRefundInsufficientFunds    = -2302,
    IZSDKPayPalQRCRefundFailed               = -2303,
    IZSDKPayPalQRCRefundCancelled            = -2304,
};

/// Used in the `IZSDKPayPalQRCPaymentInfo` object to represent what Payment provider customer used to pay.
///
/// **Note:** It's possible for customer to pay for Paypal QR-code with Venmo app and vice versa.
typedef NS_ENUM(NSInteger, IZSDKPayPalQRCType) {
    IZSDKPayPalQRCTypePayPal = 0,
    IZSDKPayPalQRCTypeVenmo = 1
};

@interface IZSDKPayPalQRCPaymentInfo: NSObject

/// Total transaction amount.
@property (nonatomic, readonly) NSDecimalNumber *amount;

/// Zettle's reference to the payment that should be displayed on receipts (not to be confused with the reference provided by you during a charge or refund operation).
@property (nonatomic, readonly) NSString *referenceNumber;

/// Transaction Identifier that should be displayed on receipts and comes from the PayPal service.
@property (nonatomic, readonly) NSString *paypalTransactionId;

/// Which QRC type was used to perform the payment PayPal or Venmo (USA Only).
@property (nonatomic, readonly) IZSDKPayPalQRCType type;

/// The Zettle transaction identifier for the transaction itself.
@property (nonatomic, readonly) NSString *transactionId;

@end

NS_ASSUME_NONNULL_END
