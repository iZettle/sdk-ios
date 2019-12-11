// 
// Copyright © 2019 iZettle. All rights reserved.
//

#import "IZettleOAuthToken.h"

NS_ASSUME_NONNULL_BEGIN

@interface IZTokenManager: NSObject

@property (nonatomic, readonly) _Nullable id<IZOAuthToken> oauthToken;

- (instancetype)initWithOauthToken:(id<IZOAuthToken>)oauthToken
                    elevatedTokens:(NSMutableArray<id<IZOAuthToken>>*)elevatedTokens;

- (NSString * _Nullable)elevatedTokenWith:(NSArray<OAuthTokenScope *> *)scopes;

- (void)addElevatedToken:(id<IZOAuthToken>) token;

@end

NS_ASSUME_NONNULL_END
