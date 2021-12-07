//
//  CustomAuthorizationProvider.m
//  iZettle SDK Sample
//
//  Copyright © 2015 PayPal Inc. All rights reserved.
//

#import "CustomAuthorizationProvider.h"
#import "AccountManager.h"
#import "AccessTokenFetcher.h"

#pragma mark - CustomAuthorizationProvider

@interface CustomAuthorizationProvider() <iZettleSDKAuthorizationProvider>

@property(nonatomic, readonly)NSString *clientId;
@property(nonatomic, readonly)NSURL *callback;
@property(nonatomic)AccessTokenFetcher *tokenFetcher;

@end

@implementation CustomAuthorizationProvider

#pragma mark - Initialization

- (instancetype)initWithClientId:(NSString *)clientId callbackURL:(NSURL *)callback {
    if (self = [super init]) {
        _clientId = clientId;
        _callback = callback;
        self.tokenFetcher = [[AccessTokenFetcher alloc] initWith:clientId callbackUrl:callback];
        self.tokenFetcher.safariViewControllerDidFinish = ^{
            [CustomAuthorizationProvider notifySFSafariDidFinishWithCallbackURL:nil];
        };
    }
    return self;
}

#pragma mark - Notification

+ (void)notifySFSafariDidFinishWithCallbackURL:(NSURL *)url {
    NSDictionary *userInfo = url ? @{@"url": url} : nil;
    [NSNotificationCenter.defaultCenter postNotificationName:@"CallbackNotification" object:nil userInfo:userInfo];
}

#pragma mark - iZettleSDKAuthorizationProvider Protocol conformance

- (void)authorizeAccountWithCompletion:(void (^)(iZettleSDKOAuthToken * _Nullable, NSError * _Nullable))completion {
    // Email can pre-filled in the login window
    UserAccountIdentifier *email = nil;
    NSArray *scopes = @[@"READ:USERINFO", @"READ:PAYMENT", @"WRITE:PAYMENT"];
    [self.tokenFetcher getTokenWithAccountIdentifier:email scopes:scopes prompt:@"login" completionHandler:completion];
}

- (void)verifyAccountWithUuid:(NSUUID * _Nonnull)uuid completion:(void (^ _Nonnull)(iZettleSDKOAuthToken * _Nullable, NSError * _Nullable))completion {
    // User UUID of the logged in account
    UserAccountIdentifier *userUUID = [[UserAccountIdentifier alloc] initWithUUID:uuid];
    NSArray *scopes = @[@"WRITE:REFUND2"];
    [self.tokenFetcher getTokenWithAccountIdentifier:userUUID scopes:scopes prompt:@"verify" completionHandler:completion];
}
@end
