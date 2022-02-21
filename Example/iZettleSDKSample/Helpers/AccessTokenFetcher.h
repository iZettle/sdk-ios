//
//  AccessTokenFetcher.h
//  iZettle SDK Sample
//
//  Copyright © 2021 PayPal Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
@import SafariServices;
@import iZettleSDK;

NS_ASSUME_NONNULL_BEGIN
@interface UserAccountIdentifier: NSObject

@property(nullable, strong, nonatomic, readonly) NSString *email;
@property(nullable, strong, nonatomic, readonly) NSUUID *uuid;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithUUID:(NSUUID *)uuid;

@end

@interface AccessTokenFetcher : NSObject <SFSafariViewControllerDelegate>
@property (nonatomic, copy) void (^safariViewControllerDidFinish)(void);
- (instancetype)initWith:(NSString *)clientId callbackUrl:(NSURL *)callbackUrl;
- (void)getTokenWithAccountIdentifier:(UserAccountIdentifier *)identifier
                               scopes:(NSArray<NSString *> *)scopes
                               prompt:(NSString *)prompt
                    completionHandler:(void (^ _Nonnull)(iZettleSDKOAuthToken *, NSError *))completion;

@end

NS_ASSUME_NONNULL_END
