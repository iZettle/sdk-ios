//
//  iZettleSDK.h
//
//  Copyright © 2014 PayPal Inc. All rights reserved.

@import UIKit;

NS_ASSUME_NONNULL_BEGIN

@class iZettleSDKPaymentInfo;
@class IZSDKPayPalQRCPaymentInfo;
@protocol iZettleSDKAuthorizationProvider;

/// SDK error domain.
extern NSErrorDomain const IZSDKErrorDomain;

/// PayPal QRC error domain.
extern NSErrorDomain const IZSDKPayPalQRCErrorDomain;

/// Defines SDK errors.
typedef NS_ERROR_ENUM(IZSDKErrorDomain, IZSDKErrorCode) {
    IZSDKErrorCodeUserNotLoggedIn            = -1,
    IZSDKErrorCodePaymentNotFound            = -100,
    IZSDKErrorCodeReferenceTooLong           = -101,
    IZSDKErrorCodeReferenceIsNil             = -102,
    IZSDKErrorCodeOperationAlreadyInProgress = -300,
    IZSDKErrorCodeInvalidAmount              = -400,
    IZSDKErrorCodeAmountTooLow               = -401,
    IZSDKErrorCodeAmountTooHigh              = -402,
    IZSDKErrorCodeDeviceNotSupported         = -403,
    IZSDKErrorCodeNotEligible                = -404,
    IZSDKErrorCodeAccountNotLinked           = -405,
    IZSDKErrorCodeNoNetwork                  = -406,
    IZSDKErrorCodeUnableToPresentView        = -407
};

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

typedef void(^iZettleSDKOperationCompletion)(iZettleSDKPaymentInfo * _Nullable paymentInfo, NSError * _Nullable error);

typedef void(^IZSDKPayPalQRCCompletion)(IZSDKPayPalQRCPaymentInfo * _Nullable paymentInfo, NSError * _Nullable error);

/// Used to set up the UI that should be presented in the PayPal payment flow - `PayPal` or `Venmo`.
typedef NS_ENUM(NSInteger, IZSDKPayPalQRCAppearance) {
    IZSDKPayPalQRCAppearancePayPal = 0,
    IZSDKPayPalQRCAppearanceVenmo = 1
};

typedef NS_ENUM(NSInteger, IZSDKAlternativePaymentMethod) {
    /// This payment method represents both `PayPal` and `Venmo` since we are considering `Venmo` as a subtype of `PayPal`.
    IZSDKAlternativePaymentMethodPayPalQRC = 0,
#if DEBUG
    /// This payment method allows manually entering the customer's card details. Read more about it at [developer portal](https://developer.zettle.com/docs/ios-sdk/)
    IZSDKAlternativePaymentMethodManualCardEntry = 1
#endif
};

/// Defining which tipping style to be used when initiating a payment with tipping.
///
/// Read more at [developer portal](https://developer.zettle.com/docs/ios-sdk/concepts/tipping-support) to understand which type(s) your market supports and what the difference between tipping styles are.
///
/// **Important:** If your market does not support the selected style then the market default will be used.
typedef NS_ENUM(NSUInteger, IZSDKTippingStyle) {
    /// Disable tipping option.
    IZSDKTippingStyleNone = 0,
    
    /// The market default option.
    IZSDKTippingStyleMarketDefault,
    
    /// An amount based option.
    IZSDKTippingStyleAmount,
    
    ///A percentage based option.
    IZSDKTippingStylePercentage
};

@interface iZettleSDK : NSObject

@property (nonatomic, readonly) NSString *version;

+ (iZettleSDK *)shared;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// Initializes SDK.
///
/// This method performs validation checks.
///
/// - Parameters:
///     - provider: An object conforming to iZettleSDKAuthorizationProtocol to perform authorization.
///     For default implementation provided by iZettle use `iZettleSDKAuthorizationProvider`.
///
/// - Throws: Raises an exception if any configuration step fails.
- (void)startWithAuthorizationProvider:(id<iZettleSDKAuthorizationProvider>)provider;

/// Initializes SDK.
///
/// This method performs validation checks.
///
/// - Parameters:
///     - provider: An object conforming to iZettleSDKAuthorizationProtocol to perform authorization.
///     For default implementation provided by iZettle use `iZettleSDKAuthorizationProvider`.
///     - enableDeveloperMode: Developer mode lets you quickly test the SDK payment and refund responses of sample or production code with minimal preparation. You do not need a card reader, authorisation flow, or have a Zettle merchant account. In developer mode, you will be able to test payment, refund, and errors for card, PayPal QRC, and Venmo QRC.
///
/// - Throws: Raises an exception if any configuration step fails.
- (void)startWithAuthorizationProvider:(id<iZettleSDKAuthorizationProvider>)provider
                   enableDeveloperMode:(BOOL)enableDeveloperMode;

/// Set enabled Alternative payment methods in the SDK.
///
/// - Parameters:
///     - enabledAPMs: An array where all values should be cases of the `IZSDKAlternativePaymentMethod` enum.
- (void)setEnabledAlternativePaymentMethods:(NSArray<NSNumber *> *)enabledAPMs;

@end

@interface iZettleSDK (Operations)

/// Logout current account.
- (void)logout;

/// Perform a payment with an amount and a reference.
///
/// > Tip: Deprecated. Use ``chargeAmount:tippingStyle:reference:presentFromViewController:completion:`` instead.
///
/// > Important: Enabling tipping does not guarantee that tipping flow will be displayed. Tipping flow will only be displayed for logged in account and active reader supports tipping.
///
/// > Note: If developer mode is enabled, taking payments will not trigger real transactions.
///
/// - Parameters:
///     - amount: The amount to be charged in the logged in users currency.
///     - enableTipping: Enable tipping flow with IZSDKTippingStyleMarketDefault tipping style.
///     - reference: The payment reference. Used to identify an Zettle payment, used when retrieving payment information at a later time or performing a refund. Max length 128. (Optional).
///     - viewController: A controller from which Zettle will present its UI.
///     - completion: Completion handler that will be called when the operation finishes.
- (void)chargeAmount:(NSDecimalNumber *)amount
       enableTipping:(BOOL)enableTipping
           reference:(nullable NSString *)reference
presentFromViewController:(UIViewController *)viewController
          completion:(iZettleSDKOperationCompletion)completion
NS_SWIFT_NAME(charge(amount:enableTipping:reference:presentFrom:completion:))
__deprecated_msg("Use chargeAmount:tippingStyle:reference:presentFromViewController:completion: instead.");

/// Perform a payment with an amount, tipping style and a reference.
///
/// > Important: Setting a tipping style does not guarantee that tipping flow will be displayed. Tipping flow will only be displayed for logged in account supporting specificed style and  active reader supporting tipping.
///
/// > Note: If developer mode is enabled, taking payments will not trigger real transactions.
///
/// - Parameters:
///     - amount: The amount to be charged in the logged in users currency.
///     - tippingStyle: Selecting a tipping style or `None` to disable tipping for this payment.
///     - reference: The payment reference. Used to identify an iZettle payment, used when retrieving payment information at a later time or performing a refund. Max length 128. (Optional).
///     - viewController: A controller from which iZettle will present its UI.
///     - completion: Completion handler that will be called when the operation finishes.
- (void)chargeAmount:(NSDecimalNumber *)amount
        tippingStyle:(IZSDKTippingStyle)tippingStyle
           reference:(nullable NSString *)reference
presentFromViewController:(UIViewController *)viewController
          completion:(iZettleSDKOperationCompletion)completion
NS_SWIFT_NAME(charge(amount:tippingStyle:reference:presentFrom:completion:));

/// Refund an amount from a payment with a given reference.
///
/// > Note: If developer mode is enabled, making refunds will not trigger real transactions.
///
/// - Parameters:
///     - amount: The amount to be refunded from the payment (Optional, `nil` will refund full amount of original payment).
///     - reference: The reference of the payment that is to be refunded.
///     - refundReference: The reference of the refund. Max length 128. (Optional)
///     - viewController: A controller from which iZettle will present its UI.
///     - completion: Completion handler that will be called when the operation finishes.
- (void)refundAmount:(nullable NSDecimalNumber *)amount
ofPaymentWithReference:(NSString *)reference
     refundReference:(nullable NSString *)refundReference
presentFromViewController:(UIViewController *)viewController
          completion:(iZettleSDKOperationCompletion)completion
NS_SWIFT_NAME(refund(amount:ofPayment:withRefundReference:presentFrom:completion:));;

/// Query iZettle for payment information of a payment with a given reference.
///
/// - Parameters:
///     - reference: The payment reference to query.
///     - viewController: A controller from which iZettle will present its UI.
///     - completion: Completion handler that will be called when the operation finishes.
- (void)retrievePaymentInfoForReference:(NSString *)reference
              presentFromViewController:(UIViewController *)viewController
                             completion:(iZettleSDKOperationCompletion)completion
NS_SWIFT_NAME(retrievePaymentInfo(for:presentFrom:completion:));

/// Query iZettle for payment information of a payment with a given reference.
///
/// - Parameters:
///     - reference: The payment reference to query.
///     - completion: Completion handler that will be called when the operation finishes.
- (void)retrievePaymentInfoForReference:(NSString *)reference
                             completion:(iZettleSDKOperationCompletion)completion
NS_SWIFT_NAME(retrievePaymentInfo(for:completion:));

/// Perform a PayPal QRC payment with an amount and a reference.
///
/// > Important: Supposed to be used for PayPal QRC DE and UK integrations.
///
/// > Note: If developer mode is enabled, taking payments will not trigger real transactions.
///
/// - Parameters:
///     - amount: The amount to be charged in the logged-in user's currency.
///     - reference: Non-nullable payment reference. Used to identify a Zettle payment when retrieving payment information at a later time, or performing a refund. Max length 128.
///     - viewController: A controller from which iZettle will present its UI.
///     - completion: Completion handler that will be called when the operation finishes.
- (void)chargePayPalQRCWithAmount:(NSDecimalNumber *)amount
                        reference:(NSString *)reference
      presentedFromViewController:(UIViewController *)viewController
                       completion:(IZSDKPayPalQRCCompletion)completion
NS_SWIFT_NAME(chargePayPalQRC(amount:reference:presentFrom:completion:))
API_AVAILABLE(ios(13));

/// Perform a PayPal QRC payment with an amount and a reference.
/// Triggers PayPal or Venmo flow based on the appearance provided.
///
/// > Important: Supposed to be used for PayPal QRC US and Venmo QRC US integration.
///
/// > Note: It's possible for a buyer to pay with `Venmo` for PayPal QRC payment and with `PayPal` for Venmo QRC payment. You can check the payment provider chosen by a buyer in the completion object.
///
/// > Note: If developer mode is enabled, taking payments will not trigger real transactions.
///
/// - Parameters:
///     - amount: The amount to be charged in the logged-in user's currency.
///     - reference: Non-nullable payment reference. Used to identify a Zettle payment when retrieving payment information at a later time, or performing a refund. Max length 128.
///     - viewController: A controller from which iZettle will present its UI.
///     - completion: Completion handler that will be called when the operation finishes. Contains information about the payment type chosen by  a buyer to pay for the presented QR-code.
- (void)chargePayPalQRCWithAmount:(NSDecimalNumber *)amount
                        reference:(NSString *)reference
                       appearance:(IZSDKPayPalQRCAppearance)appearance
        presentFromViewController:(UIViewController *)viewController
                       completion:(IZSDKPayPalQRCCompletion)completion
NS_SWIFT_NAME(chargePayPalQRC(amount:reference:appearance:presentFrom:completion:))
API_AVAILABLE(ios(13));

/// Query Zettle for payment information of a PayPal QRC (and Venmo QRC) payment and refund with a given reference.
///
/// > Important: Triggers login flow if there is no currently logged in user in the SDK.
///
/// - Parameters:
///     - reference: The payment/refund reference to query. Use the same reference as was used on the payment/refund initialization.
///     - viewController: A controller from which Zettle will present its UI.
///     - completion: Completion handler that will be called when the operation finishes.
- (void)retrievePayPalQRCPaymentInfoForReference:(NSString *)reference
                       presentFromViewController:(UIViewController *)viewController
                                      completion:(IZSDKPayPalQRCCompletion)completion
NS_SWIFT_NAME(retrievePayPalQRCPaymentInfo(for:presentFrom:completion:))
API_AVAILABLE(ios(13));

/// Query Zettle for payment information of a PayPal QRC (and Venmo QRC) payment and refund with a given reference.
///
/// - Parameters:
///     - reference: The payment/refund reference to query. Use the same reference as was used on the payment/refund initialization.
///     - completion: Completion handler that will be called when the operation finishes.
///
/// - Throws: Error is thrown if there is no currently logged in user in the SDK.
- (void)retrievePayPalQRCPaymentInfoForReference:(NSString *)reference
                                      completion:(IZSDKPayPalQRCCompletion)completion
NS_SWIFT_NAME(retrievePayPalQRCPaymentInfo(for:completion:))
API_AVAILABLE(ios(13));

/// Refund an amount from a PayPal QRC payment with a given reference.
///
/// > Note: If developer mode is enabled, making refunds will not trigger real transactions.
///
/// - Parameters:
///     - amount: The nullable amount to be refunded from the payment (passing `nil` will refund the full amount of the original payment).
///     - reference: The reference of the payment that is to be refunded.
///     - refundReference: Non-nullable refund reference. Used to identify a Zettle refund when retrieving refund information at a later time. Max length 128.
///     - viewController:  A controller from which Zettle will present its UI.
///     - completion: Completion handler that will be called when the operation finishes.
- (void)refundPayPalQRCAmount:(nullable NSDecimalNumber *)amount
       ofPaymentWithReference:(NSString *)paymentReference
              refundReference:(NSString *)refundReference
    presentFromViewController:(UIViewController *)viewController
                   completion:(IZSDKPayPalQRCCompletion)completion
NS_SWIFT_NAME(refundPayPalQRC(amount:ofPayment:withRefundReference:presentFrom:completion:))
API_AVAILABLE(ios(13));

/// Present iZettle settings view. The user can switch account, access the iZettle FAQ, view card reader settings etc.
///
/// - Parameters:
///     - viewController:  A controller from which iZettle will present its UI.
- (void)presentSettingsFromViewController:(UIViewController *)viewController
NS_SWIFT_NAME(presentSettings(from:));

/// Call from application:openURL:options: in the UIApplicationDelegate as part of the authorization flow.
///
/// > Important: Only used for targets supporting iOS 9 and 10, applications targeting newer iOS versions can omit this step.
///
/// - Parameters:
///     - url: from openURL.
///
/// - Returns: `true` if the url is handled, `false` otherwise.
- (BOOL)applicationDidOpenWithURL:(NSURL *)url NS_DEPRECATED_IOS(9_0, 11_0, "Not needed on newer iOS versions.")
NS_SWIFT_NAME(applicationDidOpen(with:));

/// Attempt aborting the ongoing operation. Only use this if absolutely necessary. The state of the payment will be unknown to the user after this call.
- (void)abortOperation;

@end

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
