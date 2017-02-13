//
//  iZettleSDK.h
//
//  Copyright (c) 2014 iZettle. All rights reserved.

@import UIKit;

NS_ASSUME_NONNULL_BEGIN

@class iZettleSDKPaymentInfo;

typedef void(^iZettleSDKOperationCompletion)(iZettleSDKPaymentInfo * _Nullable paymentInfo, NSError * _Nullable error);

@interface iZettleSDK : NSObject

@property (nonatomic, readonly) NSString *version;

+ (iZettleSDK *)shared;
- (void)startWithAPIKey:(NSString *)apiKey;

/// If set only an iZettle user with this account will be allowed to be logged in.
@property (nonatomic, copy, nullable) NSString *enforcedUserAccount;

@end

@interface iZettleSDK (Operations)

/// Perform a payment with an amount and a reference.
/// @param amount:      The amount to be charged in the logged in users currency.
/// @param currency:    Only used for validation. If the value of this parameter doesn't match the users currency the user will be notified and then logged out. For a complete list of valid currency codes, see ISO 4217 (Optional)
/// @param reference:   The payment reference. Used to identify an iZettle payment, used when retrieving payment information at a later time or performing a refund. Max length 128. (Optional)
/// @param viewController:  A controller from which iZettle will present its UI.
/// @param completion:  Completion handler that will be called when the operation finishes.
- (void)chargeAmount:(NSDecimalNumber *)amount
            currency:(nullable NSString *)currency
           reference:(nullable NSString *)reference
presentFromViewController:(UIViewController *)viewController
          completion:(iZettleSDKOperationCompletion)completion;

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
          completion:(iZettleSDKOperationCompletion)completion;

/// Query iZettle for payment information of a payment with a given reference.
/// @param reference:       The payment reference to query.
/// @param viewController:  A controller from which iZettle will present its UI.
/// @param completion:      Completion handler that will be called when the operation finishes.
- (void)retrievePaymentInfoForReference:(NSString *)reference
              presentFromViewController:(UIViewController *)viewController
                             completion:(iZettleSDKOperationCompletion)completion;

/// Present iZettle settings view. The user can switch account, access the iZettle FAQ, view card reader settings etc.
/// @param viewController:  A controller from which iZettle will present its UI.
- (void)presentSettingsFromViewController:(UIViewController *)viewController;

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

@end

NS_ASSUME_NONNULL_END
