// 
// Copyright © 2019 iZettle. All rights reserved.
// 

#import "OAuthTokenScope.h"

@import iZettleShared;

NS_ASSUME_NONNULL_BEGIN

@protocol IZOAuthToken

@property (readonly) NSString *accessToken;
@property (readonly) NSString *refreshToken;
@property (readonly) BOOL isElevated;
@property (readonly) BOOL isExpired;
- (IZFuture *)refresh;
- (NSDictionary *)representation;

@end

extern NSString *const IZMigrationToken;

@interface IZettleOAuthToken : NSObject<IZOAuthToken>

- (instancetype)initWithData:(NSData *)jsonData;
- (instancetype)initWithJson:(NSDictionary *)json;

@property(copy, readonly) NSDictionary *json;
@property(copy) IZFuture<NSDictionary *> *(^refreshCallback)(NSString *refreshToken);

- (BOOL) hasPermissionFor:(NSArray<OAuthTokenScope *> *)scopes;

NS_ASSUME_NONNULL_END

@end


