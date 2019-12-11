// 
// Copyright © 2019 iZettle. All rights reserved.
// 

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

/// SDK error domain
extern NSErrorDomain const IZSDKErrorDomain;

/**
 Defines errors that can occur during payment flow in SDK
 */
typedef NS_ERROR_ENUM(IZSDKErrorDomain, IZSDKErrorCode) {
    IZSDKErrorCodeUserNotLoggedIn            = -1, // Remap of `AccountErrorCodeUserNotLoggedIn`
    IZSDKErrorCodePaymentNotFound            = -100, // Remap of `PaymentErrorCodePaymentNotFound`
    IZSDKErrorCodeReferenceTooLong           = -101, // Remap of `ExternalErrorCodeReferenceTooLong`
    IZSDKErrorCodeReconnectionFailed         = -200, // Reconnecting to `iZettle Reader 2` did fail
    IZSDKErrorCodeOperationAlreadyInProgress = -300, // Remap of `AccountErrorCodeOperationAlreadyInProgress`
};

@interface NSError (PaymentsSDK)

/**
 Convenience method to create new error from `IZSDKErrorCode`.

 @param IZSDKErrorCode error code
 */
+ (NSError *)iz_SDKErrorWithCode:(IZSDKErrorCode)code;

/**
 Check to see whether error is of type `IZSDKError`

 @param IZSDKErrorCode error code to compare with NSError.
 */
- (BOOL)iz_isSDKErrorWithCode:(IZSDKErrorCode)code;

@end

NS_ASSUME_NONNULL_END
