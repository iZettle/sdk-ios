//
//  AccessTokenFetcher.m
//  iZettle SDK Sample
//
//  Copyright © 2021 PayPal Inc. All rights reserved.
//

#import "AccessTokenFetcher.h"
@import CommonCrypto;
@import iZettleSDK;

static NSString *baseURL = @"https://oauth.izettle.com";

#pragma mark - UserAccountIdentifier

@implementation UserAccountIdentifier

- (instancetype)initWithEmail:(NSString *)email {
    if ([super init]) {
        _email = email;
    }
    return self;
}

- (instancetype)initWithUUID:(NSUUID *)uuid {
    if ([super init]) {
        _uuid = uuid;
    }
    return self;
}
@end

@interface AccessTokenFetcher()
@property(nonatomic)NSString *clientId;
@property(nonatomic)NSURL *callback;
@end

@implementation AccessTokenFetcher

- (instancetype)initWith:(NSString *)clientId callbackUrl:(NSURL *)callbackUrl {
    if (self = [super init]) {
        self.clientId = clientId;
        self.callback = callbackUrl;
    }
    return self;
}

- (void)getTokenWithAccountIdentifier:(UserAccountIdentifier *)identifier
                               scopes:(NSArray<NSString *> *)scopes
                               prompt:(NSString *)prompt
                    completionHandler:(void (^ _Nonnull)(iZettleSDKOAuthToken *, NSError *))completion {
    NSString *verifier = [self codeVerifier];
    NSString *state = [NSUUID UUID].UUIDString;
    NSURL *requestURL = [self authorizationURLWithScopes:scopes
                                              promptType:prompt
                                       accountIdentifier:identifier
                                                verifier:verifier
                                                   state:state];
    
    // Show login webview and recieve code in the callback
    SFSafariViewController *safari = [[SFSafariViewController alloc] initWithURL:requestURL];
    safari.delegate = self;
    [UIApplication.sharedApplication.keyWindow.rootViewController presentViewController:safari animated:YES completion:nil];
    
    __weak AccessTokenFetcher *wSelf = self;
    [self asyncAwaitSafariResponse:^(NSURL *callbackURL) {
        [safari dismissViewControllerAnimated:YES completion:nil];
        
        // Cancelled by user
        if (!callbackURL) {
            completion(nil, [NSError errorWithDomain:@"login.domain" code:-1 userInfo:nil]);
            return;
        }
        
        NSURLComponents *urlComponents = [NSURLComponents componentsWithURL:callbackURL resolvingAgainstBaseURL:NO];
        NSArray *queryItems = urlComponents.queryItems;
        BOOL validCallback = [queryItems filteredArrayUsingPredicate:[NSPredicate predicateWithFormat:@"name == 'state' AND value == %@", state]].count;
        NSURLQueryItem *codeItem = [queryItems filteredArrayUsingPredicate:[NSPredicate predicateWithFormat:@"name == 'code'"]].firstObject;
        
        // Invalid callback url
        if (!validCallback || !codeItem) {
            completion(nil, [NSError errorWithDomain:@"login.domain" code:-1 userInfo:nil]);
            return;
        }
        
        [wSelf getTokenUsingCode:codeItem.value verifier:verifier completionHandler:completion];
    }];
    
}

/// Await response either from `ApplicationDelegate` or `SFSafariViewControllerDelegate`
/// @discussion For iOS > 10 `SFAuthenticationSession` or `ASWebAuthenticationSession` should be used, they use `completionHandler`
/// instead of relying on `application:openURL:options:` and `safariViewControllerDidFinish`.
/// @param response Callback url containing session and code
- (void)asyncAwaitSafariResponse:(void (^ _Nonnull)(NSURL  * _Nullable))response {
    __weak NSNotificationCenter *center = NSNotificationCenter.defaultCenter;
    id __block observer = [NSNotificationCenter.defaultCenter addObserverForName:@"CallbackNotification"
                                                                  object:nil
                                                                   queue:nil
                                                              usingBlock:^(NSNotification * _Nonnull note) {
        response(note.userInfo[@"url"]);
        [center removeObserver:observer];
    }];
}

/// Exchange code from the callback for an iZettle OAuth token
- (void)getTokenUsingCode:(NSString *)code verifier:(NSString *)verifier completionHandler:(void (^ _Nonnull)(iZettleSDKOAuthToken *, NSError *))completion{
    NSMutableURLRequest *tokenRequest = [NSMutableURLRequest requestWithURL:[self tokenURL]];
    tokenRequest.HTTPBody = [self tokenBodyWithCode:code verifier:verifier];
    tokenRequest.HTTPMethod = @"POST";
    [tokenRequest addValue:@"application/x-www-form-urlencoded" forHTTPHeaderField:@"Content-Type"];
    NSURLSession *session = [NSURLSession sessionWithConfiguration: NSURLSessionConfiguration.defaultSessionConfiguration];
    NSURLSessionDataTask *task = [session dataTaskWithRequest:tokenRequest
                                            completionHandler:^(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable error) {
        if (!error) {
            NSError *error;
            iZettleSDKOAuthToken *token = [[iZettleSDKOAuthToken alloc] initWithData:data error:&error];
            if (!error) {
                completion(token, nil);
                return;
            }
            completion(nil, error);
        } else {
            completion(nil, error);
        }
    }];
    [task resume];
}

#pragma mark - SFSafariViewControllerDelegate

- (void)safariViewControllerDidFinish:(SFSafariViewController *)controller {
    self.safariViewControllerDidFinish();
}

#pragma mark - PKCE
// For more information visit:
// https://auth0.com/docs/api-auth/tutorials/authorization-code-grant-pkce

- (NSString *)codeVerifier {
    NSMutableData *data = [NSMutableData dataWithLength:32];
    int status = SecRandomCopyBytes(kSecRandomDefault, 32, data.mutableBytes);
    if (status != errSecSuccess) {
        // Handle error
    }
    return [[[[data base64EncodedStringWithOptions:0]
              stringByReplacingOccurrencesOfString:@"+" withString:@"-"]
             stringByReplacingOccurrencesOfString:@"/" withString:@"_"]
            stringByTrimmingCharactersInSet:[NSCharacterSet characterSetWithCharactersInString:@"="]];
}

- (NSString *)codeChallenge: (NSString *)verifier {
    // You need to import CommonCrypto
    u_int8_t buffer[CC_SHA256_DIGEST_LENGTH * sizeof(u_int8_t)];
    memset(buffer, 0x0, CC_SHA256_DIGEST_LENGTH);
    NSData *data = [verifier dataUsingEncoding:NSUTF8StringEncoding];
    CC_SHA256([data bytes], (CC_LONG)[data length], buffer);
    NSData *hash = [NSData dataWithBytes:buffer length:CC_SHA256_DIGEST_LENGTH];
    return [[[[hash base64EncodedStringWithOptions:0]
              stringByReplacingOccurrencesOfString:@"+" withString:@"-"]
             stringByReplacingOccurrencesOfString:@"/" withString:@"_"]
            stringByTrimmingCharactersInSet:[NSCharacterSet characterSetWithCharactersInString:@"="]];
}

#pragma mark - URL

- (NSURL *)authorizationURLWithScopes:(NSArray<NSString *>*)scopes
                           promptType:(NSString *)prompt
                    accountIdentifier:(UserAccountIdentifier *)accountIdentifier
                             verifier:(NSString *)verifier
                                state:(NSString *)state {
    NSArray<NSURLQueryItem *> *queryItems = @[
        [NSURLQueryItem queryItemWithName:@"client_id" value:self.clientId],
        [NSURLQueryItem queryItemWithName:@"code_challenge" value:[self codeChallenge:verifier]],
        [NSURLQueryItem queryItemWithName:@"code_challenge_method" value:@"S256"],
        [NSURLQueryItem queryItemWithName:@"locale" value:@"en-GB"],
        [NSURLQueryItem queryItemWithName:@"prompt" value:prompt],
        [NSURLQueryItem queryItemWithName:@"redirect_uri" value:self.callback.absoluteString],
        [NSURLQueryItem queryItemWithName:@"response_type" value:@"code"],
        [NSURLQueryItem queryItemWithName:@"scope" value:[scopes componentsJoinedByString:@" "]],
        [NSURLQueryItem queryItemWithName:@"state" value:state]
    ];
    
    if (accountIdentifier.email.length) {
        queryItems = [queryItems arrayByAddingObject:[NSURLQueryItem queryItemWithName:@"username"
                                                                                 value:accountIdentifier.email]];
    } else if (accountIdentifier.uuid) {
        queryItems = [queryItems arrayByAddingObject:[NSURLQueryItem queryItemWithName:@"login_hint_type"
                                                                                 value:@"uuid"]];
        queryItems = [queryItems arrayByAddingObject:[NSURLQueryItem queryItemWithName:@"login_hint"
                                                                                 value:accountIdentifier.uuid.UUIDString]];
    }
    
    NSURLComponents *components = [[NSURLComponents alloc] initWithString:baseURL];
    components.path = @"/authorize";
    components.queryItems = queryItems;
    
    return [components URL];
}

- (NSURL *)tokenURL {
    return [[NSURL URLWithString:baseURL] URLByAppendingPathComponent:@"token"];
}

- (NSData *)tokenBodyWithCode:(NSString *)code verifier:(NSString *)verifier{
    NSURLComponents *queryComponents = [[NSURLComponents alloc] init];
    queryComponents.queryItems = @[
        [NSURLQueryItem queryItemWithName:@"code" value:code],
        [NSURLQueryItem queryItemWithName:@"code_verifier" value:verifier],
        [NSURLQueryItem queryItemWithName:@"client_id" value:self.clientId],
        [NSURLQueryItem queryItemWithName:@"grant_type" value:@"authorization_code"],
        [NSURLQueryItem queryItemWithName:@"redirect_uri" value:self.callback.absoluteString]
    ];
    
    return [queryComponents.query dataUsingEncoding:NSUTF8StringEncoding];
}

@end
