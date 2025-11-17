//
//  iZettleSDK.h
//
//  Copyright © 2014 PayPal Inc. All rights reserved.

#import <UIKit/UIKit.h>
#import <iZettleSDK/IZSDKManualCardEntryPaymentInfo.h>
#import <iZettleSDK/iZettleSDKPaymentInfo.h>
#import <iZettleSDK/IZSDKPayPalQRCPaymentInfo.h>

NS_ASSUME_NONNULL_BEGIN

@class iZettleSDKPaymentInfo;
@class IZSDKPayPalQRCPaymentInfo;
@class IZSDKManualCardEntryPaymentInfo;
@protocol iZettleSDKAuthorizationProvider;
@protocol ZettleUserAuthorizationDelegate;

typedef void(^iZettleSDKOperationCompletion)(iZettleSDKPaymentInfo * _Nullable paymentInfo, NSError * _Nullable error);

@interface IZSDKSettingsConfiguration: NSObject

/// If `true`, the PayPal reader settings are presented and user has an option to switch between tipping styles and change predefined values. For this user configured settings to take an effect, the payment should be triggered with `SDKConfigured` tipping style for PayPal Reader model.
@property (nonatomic, readonly) BOOL paypalReaderTippingSettingsEnabled;

- (instancetype)initWithPayPalReaderTippingSettingsEnabled:(BOOL)paypalReaderTippingSettingsEnabled
NS_SWIFT_NAME(init(paypalReaderTippingSettingsEnabled:));

@end

@interface iZettleSDK : NSObject

@property (nonatomic, readonly) NSString *version;

/// Indicates whether a user is currently logged in to the Zettle SDK.
/// Returns `YES` if a user is authenticated and logged in, otherwise `NO`.
@property (nonatomic, readonly) BOOL isLoggedIn;

+ (iZettleSDK *)shared;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@property (weak, nonatomic) id<ZettleUserAuthorizationDelegate> authorizationObserver;
 
/// Initializes SDK.
///
/// This method performs validation checks.
///
/// - Parameters:
///     - provider: An object conforming to iZettleSDKAuthorizationProtocol to perform authorization.
///     For default implementation provided by Zettle use `iZettleSDKAuthorizationProvider`.
///
/// - Throws: Raises an exception if any configuration step fails.
- (void)startWithAuthorizationProvider:(id<iZettleSDKAuthorizationProvider>)provider;

/// Set PayPal partner attribution ID.
///
/// > Important: Used only for card payments.
///
///  - Parameters:
///     - partnerAttributionId: BN (Build Notation) code is a code that is created by Partner managers, SGMs or sales in order to track activity of sellers on a partner platform.  The code provided is sent within the Card payments API calls.
- (void)setCardPaymentPayPalPartnerAttributionId:(nullable NSString *)partnerAttributionId;

/// Returns current PayPal partner attribution ID which was set using the `setCardPaymentPayPalPartnerAttributionId:` method above
///
/// > Important: Used only for card payments.
///
/// - Returns: PayPal partner attribution ID if present, `nil` otherwise.
- (nullable NSString *)cardPaymentPayPalPartnerAttributionId;

@end

@interface iZettleSDK (SharedOperations)
/// Logout current account.
- (void)logout;

/// Attempt aborting the ongoing operation. Only use this if absolutely necessary. The state of the payment will be unknown to the user after this call.
- (void)abortOperation;

/// Initiates the login flow by presenting Zettle authentication UI.
///
/// This method presents the Zettle login interface from the provided view controller.
/// After successful authentication, the user will be logged into the Zettle SDK and
/// can access payment functionality.
/// This method must be called from the main thread.
///
/// - Parameters:
///     - completion: Completion handler that will be called when the login operation finishes.
///       Returns nil if login is successful, otherwise returns an error object describing the failure.
- (void)performLoginWithCompletion:(void (^)(NSError * _Nullable))completion;

/// Initiates the login flow by presenting Zettle authentication UI with completion handler.
///
/// This method presents the Zettle login interface from the provided view controller.
/// After authentication attempt completes, the completion handler will be called with the result.
/// This method must be called from the main thread.
///
/// - Parameters:
///     - viewController: A controller from which Zettle will present its login UI.
///     - completion: Completion handler that will be called when the login operation finishes.
///       Returns nil if login is successful, otherwise returns an error object describing the failure.
- (void)performLoginFromViewController:(UIViewController *)viewController completion:(void (^)(NSError * _Nullable))completion;

@end

@interface iZettleSDK (Refund)

/// Query Zettle for payment information of a payment with a given reference.
///
/// - Parameters:
///     - reference: The payment reference to query.
///     - viewController: A controller from which Zettle will present its UI.
///     - completion: Completion handler that will be called when the operation finishes.
- (void)retrievePaymentInfoForReference:(NSString *)reference
              presentFromViewController:(UIViewController *)viewController
                             completion:(iZettleSDKOperationCompletion)completion
NS_SWIFT_NAME(retrievePaymentInfo(for:presentFrom:completion:));

/// Query Zettle for payment information of a payment with a given reference.
///
/// - Parameters:
///     - reference: The payment reference to query.
///     - completion: Completion handler that will be called when the operation finishes.
- (void)retrievePaymentInfoForReference:(NSString *)reference
                             completion:(iZettleSDKOperationCompletion)completion
NS_SWIFT_NAME(retrievePaymentInfo(for:completion:));

/// Refund an amount from a payment with a given reference.
///
/// > Note: If developer mode is enabled, making refunds will not trigger real transactions.
///
/// - Parameters:
///     - amount: The amount to be refunded from the payment (Optional, `nil` will refund full amount of original payment).
///     - reference: The reference of the payment that is to be refunded.
///     - refundReference: The reference of the refund. Max length 128. (Optional)
///     - viewController: A controller from which Zettle will present its UI.
///     - completion: Completion handler that will be called when the operation finishes.
- (void)refundAmount:(nullable NSDecimalNumber *)amount
ofPaymentWithReference:(NSString *)reference
     refundReference:(nullable NSString *)refundReference
presentFromViewController:(UIViewController *)viewController
          completion:(iZettleSDKOperationCompletion)completion
NS_SWIFT_NAME(refund(amount:ofPayment:withRefundReference:presentFrom:completion:));;

@end

#if  __has_include(<iZettlePayments/iZettlePayments-Swift.h>)
@interface iZettleSDK (Operations)

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

/// Initializes SDK.
///
/// This method performs validation checks.
///
/// - Parameters:
///     - provider: An object conforming to iZettleSDKAuthorizationProtocol to perform authorization.
///     For default implementation provided by Zettle use `iZettleSDKAuthorizationProvider`.
///     - enableDeveloperMode: Developer mode lets you quickly test the SDK payment and refund responses of sample or production code with minimal preparation. You do not need a card reader, authorisation flow, or have a Zettle merchant account. In developer mode, you will be able to test payment, refund, and errors for card, PayPal QRC, and Venmo QRC.
///
/// - Throws: Raises an exception if any configuration step fails.
- (void)startWithAuthorizationProvider:(id<iZettleSDKAuthorizationProvider>)provider
                   enableDeveloperMode:(BOOL)enableDeveloperMode;
@end

@interface iZettleSDK(QRC)

typedef void(^IZSDKPayPalQRCCompletion)(IZSDKPayPalQRCPaymentInfo * _Nullable paymentInfo, NSError * _Nullable error);

/// Used to set up the UI that should be presented in the PayPal payment flow - `PayPal` or `Venmo`.
typedef NS_ENUM(NSInteger, IZSDKPayPalQRCAppearance) {
    IZSDKPayPalQRCAppearancePayPal = 0,
    IZSDKPayPalQRCAppearanceVenmo = 1
};

typedef NS_ENUM(NSInteger, IZSDKAlternativePaymentMethod) {
    /// This payment method represents both `PayPal` and `Venmo` since we are considering `Venmo` as a subtype of `PayPal`.
    IZSDKAlternativePaymentMethodPayPalQRC = 0,
    /// This payment method allows manually entering the customer's card details. Read more about it at [developer portal](https://developer.zettle.com/docs/ios-sdk/)
    IZSDKAlternativePaymentMethodManualCardEntry = 1
};

/// Set enabled Alternative payment methods in the SDK.
///
/// - Parameters:
///     - enabledAPMs: An array where all values should be cases of the `IZSDKAlternativePaymentMethod` enum.
- (void)setEnabledAlternativePaymentMethods:(NSArray<NSNumber *> *)enabledAPMs;

/// Perform a PayPal QRC payment with an amount and a reference.
///
/// > Important: Supposed to be used for PayPal QRC DE and UK integrations.
///
/// > Note: If developer mode is enabled, taking payments will not trigger real transactions.
///
/// - Parameters:
///     - amount: The amount to be charged in the logged-in user's currency.
///     - reference: Non-nullable payment reference. Used to identify a Zettle payment when retrieving payment information at a later time, or performing a refund. Max length 128.
///     - viewController: A controller from which Zettle will present its UI.
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
///     - viewController: A controller from which Zettle will present its UI.
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
@end

@interface iZettleSDK(ManualCardEntry)

typedef void(^IZSDKManualCardEntryCompletion)(IZSDKManualCardEntryPaymentInfo * _Nullable paymentInfo, NSError * _Nullable error);

/// Perform a Manual card entry payment with an amount and a reference.
///
/// > Note: If developer mode is enabled, making refunds will not trigger real transactions.
///
/// - Parameters:
///     - amount: The amount to be charged in the logged-in user's currency.
///     - reference: Non-nullable payment reference. Used to identify a Zettle payment when retrieving payment information at a later time, or performing a refund.
///     - viewController: A controller from which Zettle will present its UI.
///     - completion: Completion handler that will be called when the operation finishes.
- (void)chargeManualCardEntryWithAmount:(NSDecimalNumber *)amount
                              reference:(NSUUID *)reference
              presentFromViewController:(UIViewController *)viewController
                             completion:(IZSDKManualCardEntryCompletion)completion
NS_SWIFT_NAME(chargeManualCardEntry(amount:reference:presentFrom:completion:));

/// Query Zettle for payment information of a Manual card entry payment and refund with a given reference.
///
/// > Note: If developer mode is enabled, making refunds will not trigger real transactions.
///
/// - Parameters:
///     - reference: The payment/refund reference to query. Use the same reference as was used on the payment/refund initialization.
///     - viewController: A controller from which Zettle will present its UI.
///     - completion: Completion handler that will be called when the operation finishes.
- (void)retrieveManualCardEntryInfoForReference:(NSUUID *)reference
                      presentFromViewController:(UIViewController *)viewController
                                     completion:(IZSDKManualCardEntryCompletion)completion
NS_SWIFT_NAME(retrieveManualCardEntryInfo(for:presentFrom:completion:));

/// Query Zettle for payment information of a Manual card entry payment and refund with a given reference.
///
/// > Note: If developer mode is enabled, making refunds will not trigger real transactions.
///
/// - Parameters:
///     - reference: The payment/refund reference to query. Use the same reference as was used on the payment/refund initialization.
///     - completion: Completion handler that will be called when the operation finishes.
- (void)retrieveManualCardEntryInfoForReference:(NSUUID *)reference
                                     completion:(IZSDKManualCardEntryCompletion)completion
NS_SWIFT_NAME(retrieveManualCardEntryInfo(for:completion:));

/// Refund an amount from a Manual Card Entry payment with a given reference.
///
/// > Note: If developer mode is enabled, making refunds will not trigger real transactions.
///
/// - Parameters:
///     - amount: The nullable amount to be refunded from the payment (passing `nil` will refund the full amount of the original payment).
///     - reference: The reference of the payment that is to be refunded.
///     - refundReference: Non-nullable refund reference. Used to identify a Zettle refund when retrieving refund information at a later time. Max length 128.
///     - viewController:  A controller from which Zettle will present its UI.
///     - completion: Completion handler that will be called when the operation finishes.
- (void)refundManualCardEntryAmount:(nullable NSDecimalNumber *)amount
             ofPaymentWithReference:(NSUUID *)paymentReference
                    refundReference:(NSUUID *)refundReference
          presentFromViewController:(UIViewController *)viewController
                         completion:(IZSDKManualCardEntryCompletion)completion
NS_SWIFT_NAME(refundManualCardEntry(amount:ofPayment:withRefundReference:presentFrom:completion:));

@end
#endif


NS_ASSUME_NONNULL_END
