// 
// Copyright © 2019 iZettle. All rights reserved.
// 

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

extern NSString *const TransactionFailedWithInvalidTokenNotification;
extern NSString *const TransactionErrorDomain;

typedef NS_ERROR_ENUM(TransactionErrorDomain, TransactionErrorCode) {
    TransactionErrorCodeJsonParsingError,
    TransactionErrorCodeCancelledByUser,
    TransactionErrorCodeInvalidSession,
    TransactionErrorCodeServerValidation,
    TransactionErrorCodeServerIllegalState,
    TransactionErrorCodeServerUnknownError,
    TransactionErrorCodeUnknownServerResponse,
    TransactionErrorCodeNotFound,
    TransactionErrorCodeUnsupportedReaderSoftware,
};


@interface NSError (iZettleRequests)

@property (readonly) BOOL isCancelledByUserTransactionError;
@property (readonly) BOOL isCancelledOrCancelledByUserError;

@property (readonly) BOOL isInvalidSessionTransactionError;

@property (readonly) BOOL isTransactionError;
@property (readonly) BOOL isNonUserCancelledTransactionError;
@property (readonly) BOOL isErrorToBePresentedInDeveloperMode;

- (BOOL)isTransactionErrorWithCode:(TransactionErrorCode)code;

+ (NSString *)_transactionErrorTitleForCode:(TransactionErrorCode)code;
+ (NSString *)_transactionErrorMessageForCode:(TransactionErrorCode)code;

+ (NSError *)errorWithTransactionCode:(TransactionErrorCode)code;
+ (NSError *)errorWithTransactionCode:(TransactionErrorCode)code httpStatusCode:(NSInteger)httpStatusCode responseData:(nullable NSData *)data;

+ (NSError *)unknownServerResponseTransactionError;

@end

NS_ASSUME_NONNULL_END
