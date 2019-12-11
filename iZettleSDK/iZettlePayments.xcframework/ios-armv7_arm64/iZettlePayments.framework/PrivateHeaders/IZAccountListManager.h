// 
// Copyright © 2019 iZettle. All rights reserved.
// 

#import <Foundation/Foundation.h>

@class IZAccount;

NS_ASSUME_NONNULL_BEGIN

@interface IZAccountListManager : NSObject

- (NSArray<IZAccount *> *)fetchKnownAccounts;

#ifdef DEBUG
+ (NSArray *)debugAccounts;
#endif

@end

NS_ASSUME_NONNULL_END
