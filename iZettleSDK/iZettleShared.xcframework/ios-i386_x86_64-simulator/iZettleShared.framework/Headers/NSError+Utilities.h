//
//  NSError+Utilities.h
//  iZettleShared
//
//  Created by Måns Bernhardt on 2014-09-01.
//  Copyright (c) 2014 iZettle. All rights reserved.
//

@import Foundation;
#import "IZFuture+Utilities.h"

NS_ASSUME_NONNULL_BEGIN

@interface NSError (Utilities)

+ (instancetype)errorWithDomain:(NSString *)domain code:(NSInteger)code localizedMessage:(NSString *)localizedMessage underlyingError:(NSError * _Nullable)underlyingError;
+ (instancetype)errorWithDomain:(NSString *)domain code:(NSInteger)code localizedMessage:(NSString *)localizedMessage;

+ (instancetype)errorWithDomain:(NSString *)domain code:(NSInteger)code localizedMessages:(NSDictionary *)codeToMessages;

@end

typedef void (^SuccessErrorBlock)(BOOL success, NSError *error);

extern NSString *const BasicErrorDomain;

typedef NS_ERROR_ENUM(BasicErrorDomain, BasicErrorCode) {
    BasicErrorCodeCancelledByUser,
    BasicErrorCodeUserInteractionTimeout,
    BasicErrorCodeCancelled,
    BasicErrorCodeInvalidState,
    BasicErrorCodeMissingValue,
    BasicErrorCodeTypeMismatch
};

@interface NSError (Basic)

+ (NSString * _Nullable)_basicErrorTitleForCode:(BasicErrorCode)code;
+ (NSString *)_basicErrorMessageForCode:(BasicErrorCode)code;

+ (NSError *)errorWithBasicCode:(BasicErrorCode)code userInfo:(NSDictionary * _Nullable)info;
+ (NSError *)errorWithBasicCode:(BasicErrorCode)code; 

- (BOOL)isBasicErrorWithCode:(BasicErrorCode)code;
+ (NSError *)basicCancelledByUserError;
@property (readonly) BOOL isBasicCancelledByUserError;

@end

extern NSString *const IZErrorTitleKey;
extern NSString *const IZErrorMessageKey;
extern NSString *const IZErrorResponseBodyKey;

@interface NSError (IZError)

+ (NSDictionary *)izUserInfoWithTitle:(nullable NSString *)title message:(NSString *)message;
+ (NSDictionary *)izUserInfoWithTitle:(nullable NSString *)title message:(NSString *)message info:(nullable NSDictionary *)info;

+ (instancetype)errorWithDomain:(NSString *)domain code:(NSInteger)code title:(nullable NSString *)title message:(NSString *)message;
+ (instancetype)errorWithDomain:(NSString *)domain code:(NSInteger)code message:(NSString *)message;

@property (nonatomic, readonly) NSString *izLocalizedTitle;
@property (nonatomic, readonly) NSString *izLocalizedMessage;
@property (nonatomic, readonly) NSString *izLocalizedAlertMessage;


@end


@interface NSError (IZErrorSerialization)

// Will try to parse a string with the format returned by izStringRepresenation
// Failing to do so will return a NSError without domain and error code 0
+ (NSError *)errorWithIzStringRepresentation:(NSString *)string;

// Will return the NSError in the following format:
// @"ErrorDomain(ErrorCode) - LocalizedDescription"
@property (nonatomic, readonly) NSString *izStringRepresentation;

@end



@interface IZFuture<ResultType> (ErrorHandling)

// Note: This is what's supposed to be used. (Didn't all all variants - only this clean)
+ (IZFuture<ResultType> *)displayAlertForError:(NSError *)error onViewController:(UIViewController *)viewController;

+ (IZFuture *)displayAlertForError:(NSError *)error onlyInDeveloperMode:(BOOL)onlyInDeveloperMode;
+ (IZFuture<ResultType> *)displayAlertForError:(NSError *)error;

- (IZFuture<ResultType> *)displayAlertOnError;
- (IZFuture<ResultType> *)displayBlockingAlertOnError;

+ (IZFuture<ResultType> *)displayRetryAlertForFunction:(IZFutureFunction)function onViewController:(UIViewController *)vc predicate:(NSError *(^ _Nullable)(ResultType value, NSError *error))predicate;
+ (IZFuture<ResultType> *)displayRetryAlertOnErrorForFunction:(IZFutureFunction)funtion onViewController:(UIViewController *)vc;

@end

NS_ASSUME_NONNULL_END
