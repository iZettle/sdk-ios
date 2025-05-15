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

typedef void(^iZettleSDKOperationCompletion)(iZettleSDKPaymentInfo * _Nullable paymentInfo, NSError * _Nullable error);

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
    
    /// A percentage based option.
    IZSDKTippingStylePercentage
};
__deprecated_msg("Use IZZettleReaderTippingStyle and IZPayPalReaderTippingStyle instead.");

/// Defining which tipping style to be used when initiating a payment with tipping for Zettle readers.
///
/// Read more at [developer portal](https://developer.zettle.com/docs/ios-sdk/concepts/tipping-support) to understand which type(s) your market supports and what the difference between tipping styles are.
///
/// **Important:** If your market does not support the selected style then the market default will be used.
typedef NS_ENUM(NSUInteger, IZZettleReaderTippingStyle) {
    /// Disable tipping option.
    IZZettleReaderTippingStyleNone = 0,
    
    /// The market default option.
    IZZettleReaderTippingStyleMarketDefault,
    
    /// An amount based option.
    IZZettleReaderTippingStyleAmount,
    
    /// A percentage based option.
    IZZettleReaderTippingStylePercentage
};

/// Defining which tipping style to be used when initiating a payment with tipping for PayPal readers.
///
/// Read more at [developer portal](https://developer.zettle.com/docs/ios-sdk/concepts/tipping-support) to understand which type(s) your market supports and what the difference between tipping styles are.
///
/// **Important:** If your market does not support the selected style then the market default will be used.
typedef NS_ENUM(NSUInteger, IZPayPalReaderTippingStyle) {
    /// Disable tipping option.
    IZPayPalReaderTippingStyleNone = 0,
    
    /// The market default option.
    IZPayPalReaderTippingStyleMarketDefault,
    
    /// A custom amount based option.
    IZPayPalReaderTippingStyleCustomAmount,
    
    /// A percentage based option. It can be used together with `IZSDKPredefinedTippingValues` to utilize predefined percentage options.
    IZPayPalReaderTippingStylePredefinedPercentage,
    
    /// Uses the tipping style configured by the merchant in Settings (if configured, otherwise tipping is disabled)
    ///   - Note: when using this style, ensure the Settings view is configured to display the PayPal Reader tipping Settings section. See `IZSDKSettingsConfiguration`.
    IZPayPalReaderTippingStyleSDKConfigured
};


@interface IZSDKSettingsConfiguration: NSObject

/// If `true`, the PayPal reader settings are presented and user has an option to switch between tipping styles and change predefined values. For this user configured settings to take an effect, the payment should be triggered with `SDKConfigured` tipping style for PayPal Reader model.
@property (nonatomic, readonly) BOOL paypalReaderTippingSettingsEnabled;

- (instancetype)initWithPayPalReaderTippingSettingsEnabled:(BOOL)paypalReaderTippingSettingsEnabled
NS_SWIFT_NAME(init(paypalReaderTippingSettingsEnabled:));

@end

/// A companion type specifying 3 predefined percentage options (provided option values should be between 0 and 100). To be used together with `IZPayPalReaderTippingStylePredefinedPercentage` style as part of `IZSDKTippingConfiguration`.
@interface IZSDKPredefinedTippingValues: NSObject

@property (nonatomic, readonly) NSUInteger option1;
@property (nonatomic, readonly) NSUInteger option2;
@property (nonatomic, readonly) NSUInteger option3;

- (instancetype)initWithOption1:(NSUInteger)option1
                        option2:(NSUInteger)option2
                        option3:(NSUInteger)option3;

@end


/// Describes the tipping style preferences for each reader type.
@interface IZSDKTippingConfiguration: NSObject

/// Tipping style to be used for the Zettle Reader.
@property (nonatomic, readonly) IZZettleReaderTippingStyle zettleReaderTippingStyle;
/// Tipping style to be used for the PayPal Reader. When specifying `IZPayPalReaderTippingStylePredefinedPercentage` you can optionally provide a value for `paypalReaderPredefinedTippingValues`.
@property (nonatomic, readonly) IZPayPalReaderTippingStyle paypalReaderTippingStyle;
///  Predefined percentages to be displayed on the card reader. Used only when `paypalReaderTippingStyle` is `IZPayPalReaderTippingStylePredefinedPercentage `. If nil, market default values will be used.
@property (nonatomic, readonly, strong, nullable) IZSDKPredefinedTippingValues *paypalReaderPredefinedTippingValues;

/// Create tipping configuration by providing tipping style only for Zettle Reader.
/// Tipping will be disabled for PayPal Reader.
/// - Parameter zettleReaderTippingStyle: The tipping style for Zettle reader tipping
- (instancetype)initWithZettleReaderTippingStyle:(IZZettleReaderTippingStyle)zettleReaderTippingStyle
NS_SWIFT_NAME(init(zettleReaderTippingStyle:));

/// Create tipping configuration by providing tipping style only for Zettle Reader.
/// Tipping will be disabled for Zettle Reader.
/// - Parameter paypalReaderTippingStyle: The tipping style for PayPal reader tipping
- (instancetype)initWithPayPalReaderTippingStyle:(IZPayPalReaderTippingStyle)paypalReaderTippingStyle
NS_SWIFT_NAME(init(paypalReaderTippingStyle:));

/// Create a tipping configuration with provided tipping style and predefined values for PayPal reader.
/// Pass `None` to disable tipping for this payment for this reader model.
/// Only `Percentage` tipping style supports predefined tipping values for now.
/// If `Amount` tipping style is passed alongside with predefined tipping values, the predefined values will be ignored.
/// Tipping will be disabled for Zettle Reader.
/// - Parameters:
///   - paypalReaderTippingStyle: The tipping style for PayPal reader tipping
///   - paypalReaderPredefinedTippingValues: The predefined tipping values for the PayPal reader
- (instancetype)initWithPayPalReaderTippingStyle:(IZPayPalReaderTippingStyle)paypalReaderTippingStyle
             paypalReaderPredefinedTippingValues:(IZSDKPredefinedTippingValues *)paypalReaderPredefinedTippingValues
NS_SWIFT_NAME(init(paypalReaderTippingStyle:paypalReaderPredefinedTippingValues:));

/// Create a tipping configuration with provided tipping style for PayPal Reader and Zettle Reader.
/// Pass `None` to disable tipping for this payment for corresponding reader model.
/// - Parameters:
///   - zettleReaderTippingStyle: The tipping style for Zettle reader tipping
///   - paypalReaderTippingStyle: The tipping style for PayPal reader tipping
- (instancetype)initWithZettleReaderTippingStyle:(IZZettleReaderTippingStyle)zettleReaderTippingStyle
                        paypalReaderTippingStyle:(IZPayPalReaderTippingStyle)paypalReaderTippingStyle
NS_SWIFT_NAME(init(zettleReaderTippingStyle:paypalReaderTippingStyle:));

/// Create a tipping configuration with provided tipping style and predefined values for PayPal Reader and provided tipping style for Zettle Reader.
/// Pass `None` to disable tipping for this payment for corresponding reader model.
/// Only `Percentage` tipping style supports predefined tipping values for now for PayPal Reader.
/// If `Amount` tipping style is passed alongside with predefined tipping values for PayPal Reader, the predefined values will be ignored.
/// - Parameters:
///   - zettleReaderTippingStyle: The tipping style for Zettle reader tipping
///   - paypalReaderTippingStyle: The tipping style for PayPal reader tipping
///   - paypalReaderPredefinedTippingValues: The predefined tipping values for the PayPal reader
- (instancetype)initWithZettleReaderTippingStyle:(IZZettleReaderTippingStyle)zettleReaderTippingStyle
                        paypalReaderTippingStyle:(IZPayPalReaderTippingStyle)paypalReaderTippingStyle
             paypalReaderPredefinedTippingValues:(IZSDKPredefinedTippingValues *)paypalReaderPredefinedTippingValues
NS_SWIFT_NAME(init(zettleReaderTippingStyle:paypalReaderTippingStyle:paypalReaderPredefinedTippingValues:));

/// Preconfigured tipping configuration.
/// Zettle Reader: `IZZettleReaderTippingStyleMarketDefault` is used.
/// PayPal Reader: `IZPayPalReaderTippingStyleSDKConfigured` is used.
+ (instancetype)sdkConfiguredTippingConfiguration;

/// Preconfigured tipping configuration.
/// Zettle Reader: `IZZettleReaderTippingStyleNone` is used.
/// PayPal Reader: `IZPayPalReaderTippingStyleNone` is used.
+ (instancetype)disabledTippingConfiguration;

@end

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

/// Present Zettle settings view. The user can switch account, access the Zettle FAQ, view card reader settings etc.
/// Does not enable PayPal Reader tipping settings by default - use `presentSettingsFromViewController:configuration:`
/// to explicitly configure settings instead.
///
/// - Parameters:
///     - viewController:  A controller from which Zettle will present its UI.
- (void)presentSettingsFromViewController:(UIViewController *)viewController
NS_SWIFT_NAME(presentSettings(from:))
__deprecated_msg("Use presentSettingsFromViewController:configuration: instead.");

/// Present Zettle settings view with an option to display PayPal reader tipping settings.
/// The user can switch account, access the Zettle FAQ, view card reader settings etc.
///
/// - Parameters:
///     - viewController:  A controller from which Zettle will present its UI.
///     - configuration: Defines the presentation of additional features on the SDK settings page (e.g. PayPal Reader tipping Settings).
- (void)presentSettingsFromViewController:(UIViewController *)viewController
                            configuration:(IZSDKSettingsConfiguration *)configuration
NS_SWIFT_NAME(presentSettings(from:configuration:));

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

@interface iZettleSDK(CardReader)
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
///     - enableTipping: Enable tipping flow with IZZettleReaderTippingStyleMarketDefault tipping style and IZPayPalReaderTippingStyleMarketDefault.
///     - reference: The payment reference. Used to identify a Zettle payment, used when retrieving payment information at a later time or performing a refund. Max length 128. (Optional).
///     - viewController: A controller from which Zettle will present its UI.
///     - completion: Completion handler that will be called when the operation finishes.
- (void)chargeAmount:(NSDecimalNumber *)amount
       enableTipping:(BOOL)enableTipping
           reference:(nullable NSString *)reference
presentFromViewController:(UIViewController *)viewController
          completion:(iZettleSDKOperationCompletion)completion
NS_SWIFT_NAME(charge(amount:enableTipping:reference:presentFrom:completion:))
__deprecated_msg("Use chargeAmount:tippingConfiguration:... to specify tipping style preferences for each reader type.");

/// Perform a payment with an amount, tipping style and a reference.
///
/// > Important: Setting a tipping style does not guarantee that tipping flow will be displayed. Tipping flow will only be displayed for logged in account supporting specificed style and  active reader supporting tipping.
///
/// > Note: If developer mode is enabled, taking payments will not trigger real transactions.
///
/// - Parameters:
///     - amount: The amount to be charged in the logged in users currency.
///     - tippingStyle: Select a tipping style or `None` to disable tipping for this payment.
///     - reference: The payment reference. Used to identify an Zettle payment, used when retrieving payment information at a later time or performing a refund. Max length 128. (Optional).
///     - viewController: A controller from which Zettle will present its UI.
///     - completion: Completion handler that will be called when the operation finishes.
///
/// - Note: `IZSDKTippingStyle` is deprecated. We will map the provided `tippingStyle` to the closest `IZZettleReaderTippingStyle` and `IZPayPalReaderTippingStyle` but you're strongly encoraged to migrate to providing explicit styles via `IZSDKTippingConfiguration`.
- (void)chargeAmount:(NSDecimalNumber *)amount
        tippingStyle:(IZSDKTippingStyle)tippingStyle
           reference:(nullable NSString *)reference
presentFromViewController:(UIViewController *)viewController
          completion:(iZettleSDKOperationCompletion)completion
NS_SWIFT_NAME(charge(amount:tippingStyle:reference:presentFrom:completion:))
__deprecated_msg("Use chargeAmount:tippingConfiguration:... to specify tipping style preferences for each reader type.");

/// Perform a payment with an amount, a reference and tipping configuration.
///
/// > Important: Setting a tipping style does not guarantee that tipping flow will be displayed. Tipping flow will only be displayed for logged in account supporting specificed style and  active reader supporting tipping.
///
/// > Note: If developer mode is enabled, taking payments will not trigger real transactions.
///
/// - Parameters:
///     - amount: The amount to be charged in the logged in users currency.
///     - tippingConfiguration: Provide configuration for different tipping styles used for supported reader models (Zettle Reader and PayPal Reader)
///     - reference: The payment reference. Used to identify an Zettle payment, used when retrieving payment information at a later time or performing a refund. Max length 128. (Optional).
///     - partnerPayeePricingTierId: Payee pricing tier code is a code that is created by Partner managers, SGMs or sales in order to set pricing tier.  The code provided is sent within the Card payments API calls. (Optional)
///     - viewController: A controller from which Zettle will present its UI.
///     - completion: Completion handler that will be called when the operation finishes.
- (void)chargeAmount:(NSDecimalNumber *)amount
tippingConfiguration:(IZSDKTippingConfiguration *)tippingConfiguration
           reference:(nullable NSString *)reference
payPalPartnerPayeePricingTierId:(nullable NSString *)pricingTierId
presentFromViewController:(UIViewController *)viewController
          completion:(iZettleSDKOperationCompletion)completion
NS_SWIFT_NAME(charge(amount:tippingConfiguration:reference:payPalPartnerPayeePricingTierId:presentFrom:completion:));

/// Perform a payment with an amount, a reference and tipping configuration.
///
/// > Important: Setting a tipping style does not guarantee that tipping flow will be displayed. Tipping flow will only be displayed for logged in account supporting specificed style and  active reader supporting tipping.
///
/// > Note: If developer mode is enabled, taking payments will not trigger real transactions.
///
/// - Parameters:
///     - amount: The amount to be charged in the logged in users currency.
///     - tippingConfiguration: Provide configuration for different tipping styles used for supported reader models (Zettle Reader and PayPal Reader)
///     - reference: The payment reference. Used to identify an Zettle payment, used when retrieving payment information at a later time or performing a refund. Max length 128. (Optional).
///     - viewController: A controller from which Zettle will present its UI.
///     - completion: Completion handler that will be called when the operation finishes.
- (void)chargeAmount:(NSDecimalNumber *)amount
tippingConfiguration:(IZSDKTippingConfiguration *)tippingConfiguration
           reference:(nullable NSString *)reference
presentFromViewController:(UIViewController *)viewController
          completion:(iZettleSDKOperationCompletion)completion
NS_SWIFT_NAME(charge(amount:tippingConfiguration:reference:presentFrom:completion:));
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
