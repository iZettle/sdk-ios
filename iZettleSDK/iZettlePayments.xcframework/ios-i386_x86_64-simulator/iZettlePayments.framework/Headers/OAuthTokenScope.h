// 
// Copyright © 2019 iZettle. All rights reserved.
// 

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
// FIXME: Add IZ prefix +>

typedef NS_ENUM(NSUInteger, TokenScopeType) {
    TokenScopeTypeAll,
    TokenScopeTypeRead,
    TokenScopeTypeWrite,
    TokenScopeTypeUnidentified
};

typedef NS_ENUM(NSUInteger, TokenScopeName) {
    TokenScopeNameInternal,
    TokenScopeNameFinance,
    TokenScopeNameOnlinePayment,
    TokenScopeNameProduct,
    TokenScopeNamePurchase,
    TokenScopeNameUserInfo,
    TokenScopeNameRefund,
    TokenScopeNameRefund2,
    TokenScopeNameUnidentified,
};

@interface OAuthTokenScope : NSObject

@property (nonatomic, readonly) TokenScopeType type;
@property (nonatomic, readonly) TokenScopeName name;

- (instancetype _Nullable)initFrom:(NSString *_Nullable)rawData;
- (instancetype)initWith:(TokenScopeType) type and:(TokenScopeName) name;

@end

// <+
NS_ASSUME_NONNULL_END
