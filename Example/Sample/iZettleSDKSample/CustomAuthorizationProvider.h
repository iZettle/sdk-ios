//
//  CustomAuthorizationProvider.h
//  iZettle SDK Sample
//
//  Copyright © 2015 PayPal Inc. All rights reserved.
//
#import <Foundation/Foundation.h>
@import iZettleSDK;

NS_ASSUME_NONNULL_BEGIN

@interface CustomAuthorizationProvider : NSObject <iZettleSDKAuthorizationProvider>

- (instancetype)initWithClientId:(NSString *)clientId callbackURL:(NSURL *)callback;

+ (void)notifySFSafariDidFinishWithCallbackURL:(NSURL * _Nullable)url;

@end

NS_ASSUME_NONNULL_END
