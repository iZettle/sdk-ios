//
//  iZettleSDK.h
//
//  Copyright (c) 2014 iZettle. All rights reserved.

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class iZettleSDKPaymentInfo;

typedef void(^iZettleSDKOperationCompletion)(iZettleSDKPaymentInfo * _Nullable paymentInfo, NSError * _Nullable error);

@interface iZettleSDK : NSObject

@property (nonatomic, readonly) NSString *version;

+ (iZettleSDK *)shared;
- (void)startWithAPIKey:(NSString *)apiKey;

/*! if set only an iZettle user with this account will be allowed to be logged in. */
@property (nonatomic, copy, nullable) NSString *enforcedUserAccount;

@end

@interface iZettleSDK (Operations)

/*! Perform a payment with an amount and a reference. */
- (void)chargeAmount:(NSDecimalNumber *)amount
            currency:(nullable NSString *)currency
           reference:(nullable NSString *)reference
presentFromViewController:(UIViewController *)viewController
          completion:(iZettleSDKOperationCompletion)completion;

/*! Refund a payment with a given reference. */
- (void)refundPaymentWithReference:(NSString *)reference
                   refundReference:(nullable NSString *)refundReference
         presentFromViewController:(UIViewController *)viewController
                        completion:(iZettleSDKOperationCompletion)completion;

/*! Query iZettle for payment information of a payment with a given reference. */
- (void)retrievePaymentInfoForReference:(NSString *)reference
              presentFromViewController:(UIViewController *)viewController
                             completion:(iZettleSDKOperationCompletion)completion;

/*! Present iZettle settings view. The user can switch account, access the iZettle FAQ, view card reader settings etc. */
- (void)presentSettingsFromViewController:(UIViewController *)viewController;

/*! Invalidate the current iZettle session. Use this to programmatically logout the user from iZettle. */
- (void)invalidateSession __deprecated_msg("use enforcedUserAccount instead.");

/*! Attempt aborting the ongoing operation. Only use this if absolutely necessary. The state of the payment will be unknown to the user after this call. */
- (void)abortOperation;

@end

@interface iZettleSDKPaymentInfo : NSObject

@property (nonatomic, readonly) NSDictionary<NSString *, id> *dictionary;   // Dictionary representation of the payment information

@property (nonatomic, readonly) NSString *referenceNumber;  // iZettles reference to the payment
@property (nonatomic, readonly) NSString *entryMode;        // EMV, MAGSTRIPE, MANUAL_ENTRY
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
