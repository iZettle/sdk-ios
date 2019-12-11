// 
// Copyright © 2019 iZettle. All rights reserved.
// 

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

extern NSString *const AccountErrorDomain;
extern NSString *const IZMigrationToken;

typedef NS_ERROR_ENUM(AccountErrorDomain, AccountErrorCode) {
    AccountErrorCodeUserNotLoggedIn,
    AccountErrorCodeUserNotLoggedOut,
    AccountErrorCodeInvalidAPIKey,
    AccountErrorCodeShowstopper,
    AccountErrorCodeInvalidUser,
    AccountErrorCodeInvalidCredentials,
    AccountErrorCodeTooManyFailedAttempts,
    AccountErrorCodeCancelledByUser,
    AccountErrorCodeAccountFrozen,
    AccountErrorCodeOperationAlreadyInProgress = 10, // Used in URL Scheme wrapper
    AccountErrorCodeOperationWasProgramaticallyAborted,
    AccountErrorCodeOneTimePasswordRequired,
};

@interface NSError (Account)

+ (NSString * _Nullable)_sessionErrorTitleForCode:(AccountErrorCode)code;
+ (NSString *)_sessionErrorMessageForCode:(AccountErrorCode)code;

+ (NSError *)errorWithAccountCode:(AccountErrorCode)code;
+ (NSError *)errorWithAccountCode:(AccountErrorCode)code userInfo:(NSDictionary *)info;
- (BOOL)isAccountErrorWithCode:(AccountErrorCode)code;

@end

NS_ASSUME_NONNULL_END
