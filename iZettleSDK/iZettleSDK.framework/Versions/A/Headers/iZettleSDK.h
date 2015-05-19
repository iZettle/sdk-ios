//
//  iZettleSDK.h
//
//  Copyright (c) 2014 iZettle. All rights reserved.

#import <UIKit/UIKit.h>

@class iZettleSDKPaymentInfo;

typedef void(^iZettleSDKOperationCompletion)(iZettleSDKPaymentInfo *paymentInfo, NSError *error);

@interface iZettleSDK : NSObject

@property (nonatomic, readonly) NSString *version;

+ (iZettleSDK *)shared;
- (void)startWithAPIKey:(NSString *)apiKey;

/*! if set only an iZettle user with this account will be allowed to be logged in. */
@property (nonatomic, copy) NSString *enforcedUserAccount;

@end

@interface iZettleSDK (Operations)

/*! Perform a payment with an amount and a reference. */
- (void)chargeAmount:(NSDecimalNumber *)amount
            currency:(NSString *)currency
           reference:(NSString *)reference
presentFromViewController:(UIViewController *)viewController
          completion:(iZettleSDKOperationCompletion)completion;

/*! Refund a payment with a given reference. */
- (void)refundPaymentWithReference:(NSString *)reference
                   refundReference:(NSString *)refundReference
         presentFromViewController:(UIViewController *)viewController
                        completion:(iZettleSDKOperationCompletion)completion;

/*! Query iZettle for payment information of a payment with a given reference. */
- (void)retrievePaymentInfoForReference:(NSString *)reference
                             completion:(iZettleSDKOperationCompletion)completion;

/*! Present iZettle settings view. The user can switch account, access the iZettle FAQ, view card reader settings etc. */
- (void)presentSettingsFromViewController:(UIViewController *)viewController;

/*! Invalidate the current iZettle session. Use this to programmatically logout the user from iZettle. */
- (void)invalidateSession;

/*! Attempt aborting the ongoing operation. Only use this if absolutely necessary. The state of the payment will be unknown to the user after this call. */
- (void)abortOperation;

@end

@interface iZettleSDKPaymentInfo : NSObject

@property (nonatomic, readonly) NSDictionary *dictionary;   // Dictionary representation of the payment information

@property (nonatomic, readonly) NSString *referenceNumber;  // iZettles reference to the payment
@property (nonatomic, readonly) NSString *entryMode;        // EMV, MAGSTRIPE, MANUAL_ENTRY
@property (nonatomic, readonly) NSString *authorizationCode;

@property (nonatomic, readonly) NSString *obfuscatedPan;    // **** **** **** 1111
@property (nonatomic, readonly) NSString *panHash;          // Hash sum of the plain pan
@property (nonatomic, readonly) NSString *cardBrand;

@property (nonatomic, readonly) NSString *AID;
@property (nonatomic, readonly) NSString *TSI;
@property (nonatomic, readonly) NSString *TVR;
@property (nonatomic, readonly) NSString *applicationName;

// Only used for certain markets
@property (nonatomic, readonly) NSNumber *numberOfInstallments;
@property (nonatomic, readonly) NSDecimalNumber *installmentAmount;

@end
