//
//  AppDelegate.m
//  iZettle SDK Sample
//
//  Copyright © 2015 PayPal Inc. All rights reserved.
//

#import "AppDelegate.h"
#import "CustomAuthorizationProvider.h"
#import "AccountManager.h"

@import iZettleSDK;

/// iZettle provides out of the box solution
/// but you can also provide your own OAuth 2.0 implementation,
/// for an example of how to do that - see `CustomAuthorizationProvider.h`,
/// and to try it out set `useCustomAuthorizationProvider` to `YES`
static BOOL const useCustomAuthorizationProvider = NO;
static NSString * const clientId = @"1a1f43cf-73eb-4fa2-a57d-db29b7cf9c88";
static NSString * const callbackURL = @"integration-tester://login.callback";

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    id<iZettleSDKAuthorizationProvider> authorizationProvider = [self makeAuthorizationProvider];

    ///
    /// To enable developer mode pass `true` to the `enableDeveloperMode` parameter of this function
    ///
    /// [[iZettleSDK shared] startWithAuthorizationProvider:authorizationProvider
    ///                                 enableDeveloperMode:true];
    ///
    [[iZettleSDK shared] startWithAuthorizationProvider:authorizationProvider];

    [[iZettleSDK shared] setEnabledAlternativePaymentMethods:@[@(IZSDKAlternativePaymentMethodPayPalQRC), @(IZSDKAlternativePaymentMethodManualCardEntry)]];
    return YES;
}

- (id<iZettleSDKAuthorizationProvider> _Nullable)makeAuthorizationProvider {
    if (useCustomAuthorizationProvider) {
        return [[CustomAuthorizationProvider alloc] initWithClientId:clientId callbackURL:[NSURL URLWithString:callbackURL]];
    }
    
    NSError *error;
    id<iZettleSDKAuthorizationProvider> authorizationProvider = [[iZettleSDKAuthorization alloc]
                                                                 initWithClientID:clientId
                                                                 callbackURL:[NSURL URLWithString:callbackURL]
                                                                 error:&error
                                                                 enforcedUserAccount:^NSString * _Nullable{
        return [AccountManager shared].enforcedUserAccount;
    }];
    NSAssert(!error, @"%@", error.description);
    return authorizationProvider;
}

- (BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options {
    if (useCustomAuthorizationProvider) {
        [CustomAuthorizationProvider notifySFSafariDidFinishWithCallbackURL:url];
    }
    
    return YES;
}

@end
