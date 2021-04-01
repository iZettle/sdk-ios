//
//  iZettleSDK.h
//
//  Copyright © 2014 PayPal Inc. All rights reserved.

@import UIKit;

NS_ASSUME_NONNULL_BEGIN

@class iZettleSDKPaymentInfo;
@protocol iZettleSDKAuthorizationProvider;

/// SDK error domain
extern NSErrorDomain const IZSDKErrorDomain;

/**
 Defines SDK errors
 */
typedef NS_ERROR_ENUM(IZSDKErrorDomain, IZSDKErrorCode) {
    IZSDKErrorCodeUserNotLoggedIn            = -1,
    IZSDKErrorCodePaymentNotFound            = -100,
    IZSDKErrorCodeReferenceTooLong           = -101,
    IZSDKErrorCodeReferenceIsNil             = -102,
    IZSDKErrorCodeOperationAlreadyInProgress = -300,
    IZSDKErrorCodeInvalidAmount              = -400,
    IZSDKErrorCodeAmountTooLow               = -401
};

typedef void(^iZettleSDKOperationCompletion)(iZettleSDKPaymentInfo * _Nullable paymentInfo, NSError * _Nullable error);

@interface iZettleSDK : NSObject

@property (nonatomic, readonly) NSString *version;

+ (iZettleSDK *)shared;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
 Initializes SDK
 @param provider An object conforming to iZettleSDKAuthorizationProtocol to perform authorization.
 For default implementation provided by iZettle use iZettleSDKAuthorizationProvider.
 @discussion This method performs validation checks
 @warning Raises an exception if any configuration step fails
 */
- (void)startWithAuthorizationProvider:(id<iZettleSDKAuthorizationProvider>)provider;

@end

@interface iZettleSDK (Operations)

/**
 Logout current account
 */
- (void)logout;

/**
 Perform a payment with an amount and a reference.

 @param amount The amount to be charged in the logged in users currency
 @param enableTipping Enable tipping flow
 @param reference The payment reference. Used to identify an iZettle payment, used when retrieving payment
    information at a later time or performing a refund. Max length 128. (Optional)
 @param viewController A controller from which iZettle will present its UI
 @param completion Completion handler that will be called when the operation finishes
 
 @remark Enabling tipping does not guarantee that tipping flow will be displayed. Tipping flow will only be displayed
 for logged in account and active reader supports tipping.
 */
- (void)chargeAmount:(NSDecimalNumber *)amount
       enableTipping:(BOOL)enableTipping
           reference:(nullable NSString *)reference
presentFromViewController:(UIViewController *)viewController
          completion:(iZettleSDKOperationCompletion)completion
NS_SWIFT_NAME(charge(amount:enableTipping:reference:presentFrom:completion:));

/// Refund an amount from a payment with a given reference.
/// @param amount:          The amount to be refunded from the payment (Optional, `nil` will refund full amount of original payment)
/// @param reference:       The reference of the payment that is to be refunded.
/// @param refundReference: The reference of the refund. Max length 128. (Optional)
/// @param viewController:  A controller from which iZettle will present its UI.
/// @param completion:      Completion handler that will be called when the operation finishes.
- (void)refundAmount:(nullable NSDecimalNumber *)amount
ofPaymentWithReference:(NSString *)reference
     refundReference:(nullable NSString *)refundReference
presentFromViewController:(UIViewController *)viewController
          completion:(iZettleSDKOperationCompletion)completion
NS_SWIFT_NAME(refund(amount:ofPayment:withRefundReference:presentFrom:completion:));;

/// Query iZettle for payment information of a payment with a given reference.
/// @param reference:       The payment reference to query.
/// @param viewController:  A controller from which iZettle will present its UI.
/// @param completion:      Completion handler that will be called when the operation finishes.
- (void)retrievePaymentInfoForReference:(NSString *)reference
              presentFromViewController:(UIViewController *)viewController
                             completion:(iZettleSDKOperationCompletion)completion
NS_SWIFT_NAME(retrievePaymentInfo(for:presentFrom:completion:));

/// Query iZettle for payment information of a payment with a given reference.
/// @param reference:       The payment reference to query.
/// @param completion:      Completion handler that will be called when the operation finishes.
- (void)retrievePaymentInfoForReference:(NSString *)reference
                             completion:(iZettleSDKOperationCompletion)completion
NS_SWIFT_NAME(retrievePaymentInfo(for:completion:));

/// Present iZettle settings view. The user can switch account, access the iZettle FAQ, view card reader settings etc.
/// @param viewController:  A controller from which iZettle will present its UI.
- (void)presentSettingsFromViewController:(UIViewController *)viewController
NS_SWIFT_NAME(presentSettings(from:));

/// Call from application:openURL:options: in the UIApplicationDelegate as part of the authorization flow.
/// @discussion Only used for targets supporting iOS 9 and 10, applications targeting newer iOS versions can ommit this step.
/// @param url: from openURL
/// @return true if the url is handled, false otherwise
- (BOOL)applicationDidOpenWithURL:(NSURL *)url NS_DEPRECATED_IOS(9_0, 11_0, "Not needed on newer iOS versions.")
NS_SWIFT_NAME(applicationDidOpen(with:));

/// Attempt aborting the ongoing operation. Only use this if absolutely necessary. The state of the payment will be unknown to the user after this call.
- (void)abortOperation;

@end

@interface iZettleSDKPaymentInfo : NSObject

@property (nonatomic, readonly) NSDictionary<NSString *, id> *dictionary;   // Dictionary representation of the payment information

@property (nonatomic, readonly) NSDecimalNumber *amount;    // Paid amount (including gratuityAmount)
@property (nonatomic, readonly, nullable) NSDecimalNumber *gratuityAmount; // The amount of gratuity paid

@property (nonatomic, readonly) NSString *referenceNumber;  // iZettles reference to the payment
@property (nonatomic, readonly) NSString *entryMode;        // EMV, CONTACTLESS_EMV, MAGSTRIPE_CONTACTLESS, MAGSTRIPE etc
@property (nonatomic, readonly) NSString *authorizationCode;

@property (nonatomic, readonly) NSString *obfuscatedPan;    // **** **** **** 1111
@property (nonatomic, readonly) NSString *panHash;          // Hash sum of the plain pan
@property (nonatomic, readonly) NSString *cardBrand;

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
