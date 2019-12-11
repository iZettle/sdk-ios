//
//  IZettleNetworkContext.h
//  iZettleStorePurchase
//
//  Created by Måns Bernhardt on 2015-04-24.
//  Copyright (c) 2015 iZettle. All rights reserved.
//

@import Foundation;
@import iZettleShared;

@class IZTokenManager;
@class OAuthTokenScope;

NS_ASSUME_NONNULL_BEGIN

@interface IZPinnedNetworkContext : IZNetworkContext

- (instancetype)initWithCongfiguration:(NSURLSessionConfiguration *)configuration;

@end

typedef NSDictionary<NSString *, NSArray<NSString *>  *> * ServiceURLs;

@interface IZettleNetworkContext : IZPinnedNetworkContext

+ (IZettleNetworkContext *)networkContextWithCachedURLs;

+ (IZettleNetworkContext *)networkContextWithBaseURL:(NSURL *)url;

+ (IZFuture<IZettleNetworkContext *> *)updatedNetworkContextWithBaseURL:(NSURL *)url;

- (instancetype)initWithCongfiguration:(NSURLSessionConfiguration *)configuration
                               baseURL:(NSURL *)baseURL
                           serviceURLs:(ServiceURLs)serviceURLs
                                apiKey:(NSString *)apiKey
                  apiSourceApplication:(NSString *)apiSourceApplication
                          tokenManager:(IZTokenManager *)tokenManager;

- (instancetype)initWithCongfiguration:(NSURLSessionConfiguration *)configuration
                        izettleContext:(IZettleNetworkContext *)context;

+ (void)setConfiguredBaseURL:(NSURL *)baseURL;
+ (NSURL *)getConfiguredBaseURL;

@property (nonatomic, readonly) IZTokenManager *tokenManager;
@property (readonly) NSString *apiKey;
@property (readonly) NSString *apiSourceApplication;

@property (readonly) ServiceURLs serviceURLs;

@property (readonly) NSURL *serverBaseURL;
@property (readonly) NSURL *apiBaseURL;
@property (readonly) NSURL *cardPaymentBaseURL;
@property (readonly) NSURL *authorizationServiceBaseURL;
@property (readonly) NSURL *siteBaseURL;
@property (readonly) NSURL *translationBaseURL;
@property (readonly) NSURL *webPortalBaseURL;
@property (readonly) NSURL *merchantReportBaseURL;
@property (readonly) NSURL *registrationServiceBaseURL;

@property (readonly) BOOL isProductionEnvironment;
@property (readonly) BOOL useWebAuthentication;

- (NSURL *)resolveServiceURLWithKey:(NSString *)key;

- (IZFuture<NSDictionary *> *)refreshServiceURLs;

@end


@interface IZettleNetworkContext (Networking)

// passing nil will setup request as GET instead of POST
- (IZMutableURLRequest *)requestWithURL:(NSURL *)url
                                   json:(nullable NSDictionary<NSString *, id> *)json;

- (IZMutableURLRequest *)requestWithURL:(NSURL *)url
                                   json:(nullable NSDictionary<NSString *, id> *)json
                                 scopes:(NSArray<OAuthTokenScope *>*) scopes; // using parser to json

- (IZMutableURLRequest *)requestWithURL:(NSURL *)url
                             legacyJson:(nullable NSDictionary *)json;

- (IZMutableURLRequest *)requestWithURL:(NSURL *)url
                             legacyJson:(nullable NSDictionary<NSString *, id> *)json
                                 scopes:(NSArray<OAuthTokenScope *>*) scopes;

- (IZMutableURLRequest *)requestWithURL:(NSURL *)url multiparts:(NSArray *)multiparts;

- (NSMutableDictionary *)commonPayload;

@end

@interface IZMutableURLRequest (iZettle)

- (IZFuture *)sendWithErrorAlert; // Will display error alert on failure with retry if applicable

- (IZFuture *)sendAndDisplayAlertIfDeveloperModeError;

- (IZFuture *)sendWithRetryCount:(NSInteger)retryCount retryDelay:(NSTimeInterval)retryDelay;

@property (nonatomic, assign) NSInteger backendApiVersion;

@end


@interface IZNetworkResponse (BackendResponses)

- (IZFuture<IZNetworkResponse *> *)handleNon200Errors;

- (IZFuture *)parseLegacyJson; // return Json or error
- (IZFuture *)parseJson; // return Json or error

@end

@interface IZFuture<ResultType> (BackendResponses)

- (IZFuture<ResultType> *)catchAndNotifyInvalidSessionForContext:(IZettleNetworkContext *)context;

- (IZFuture<ResultType> *)displayAlertOnNetworkError;

+ (IZFuture<ResultType> *)displayRetryAlertOnNetworkErrorForFunction:(IZFutureFunction)function;

@property (nonatomic, readonly) IZFuture<ResultType> *izRequestAnalytics;


@end

@interface NSURL (ServiceURLs)

+ (NSDictionary *)defaultServiceURLs;
+ (NSURL *)defaultBaseURL;

@end


NS_ASSUME_NONNULL_END

