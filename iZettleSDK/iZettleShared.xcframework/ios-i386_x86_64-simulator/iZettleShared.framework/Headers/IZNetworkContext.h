//
//  IZNetworkContext.h
//  iZettleShared
//
//  Created by Måns Bernhardt on 2015-04-23.
//  Copyright (c) 2015 iZettle. All rights reserved.
//

@import Foundation;
#import "IZFuture+Utilities.h"

NS_ASSUME_NONNULL_BEGIN

@interface IZNetworkResponse : NSObject 

+ (instancetype)data:(NSData *)data response:(NSURLResponse *)response;

@property (readonly, copy) NSURLResponse *response;
@property (readonly, copy) NSData *data;

@end

@interface IZNetworkResponse (Utilities)

@property (readonly, nullable) NSHTTPURLResponse *httpResponse;
@property (readonly) NSInteger httpStatusCode;

@property (readonly) NSString *contentType;

- (IZFuture<IZNetworkResponse *> *)assertContentTypePrefix:(NSString *)prefix;

@property (readonly) IZFuture *json;

@end

@interface IZNetworkResponse (Logging)

- (void)logInfoForRequestURL:(NSURL *)url httpMethod:(NSString *)httpMethod elapsedTime:(NSTimeInterval)time;
@end


@interface NSData (Networking)

@property (readonly) NSString *izUTF8String;

@end

@class IZMutableURLRequest;


@protocol IZHTTPCookieStorage

- (NSArray *)cookiesForURL:(NSURL *)theURL;
- (void)setCookie:(NSHTTPCookie *)aCookie;

@end


@interface NSURLSessionConfiguration (iZettle)

+ (NSURLSessionConfiguration *)ephemeralSessionConfigurationNoCookieStorage;

@end


typedef void (^IZNetworkProgressBlock)(int64_t byteCount, int64_t estimatedTotalsBytes);
typedef IZFuture * __nonnull (^IZNetworkResponseParser)(IZNetworkResponse *response);


@interface IZNetworkContext : NSObject

- (instancetype)initWithCongfiguration:(NSURLSessionConfiguration *)configuration delegate:(nullable id <NSURLSessionDelegate>)delegate;


- (IZFuture<IZNetworkResponse *> *)sendRequest:(IZMutableURLRequest *)request;

+ (void)addPreSendHandler:(IZFuture *(^)(IZMutableURLRequest *request))preSendHandler;
+ (void)addPostSendHandler:(IZFuture<IZNetworkResponse *> *(^)(IZMutableURLRequest *request, IZNetworkResponse *))postSendHandler;

@property (strong) id<IZHTTPCookieStorage> cookieStorage;

@end


IZNetworkContext *izSharedContext(void); // Context not tied to iZettle


@interface IZMutableURLRequest : NSMutableURLRequest

@property (nonatomic, strong) IZNetworkContext *context;

@property (copy) IZNetworkResponseParser responseParser;

@property (nonatomic, copy) IZNetworkProgressBlock sendProgressBlock;
@property (nonatomic, copy) IZNetworkProgressBlock receiveProgressBlock;

- (IZFuture *)send NS_REFINED_FOR_SWIFT;

@end


@interface NSMutableURLRequest (iZettle)

- (void)izSetJson:(id)json; // passing nil will setup request as GET instead of POST
- (NSString *)logURLString;

@end



@interface IZMultipartPart : NSObject
+ (instancetype)partWithFileName:(nullable NSString *)fileName name:(NSString *)name data:(NSData *)data;
@property (nonatomic, copy) NSString *fileName;
@property (nonatomic, copy) NSString *name;
@property (nonatomic, copy) NSData *data;
@end

@interface NSMutableURLRequest (Multipart)

+ (instancetype)requestWithURL:(NSURL *)URL multiparts:(NSArray *)multiparts;
- (void)setMultiparts:(NSArray *)multiparts; // Expects IZMultipartPart

@end



@interface IZNullCookieStorage : NSObject<IZHTTPCookieStorage>
@end

@interface IZNonPersistedCookieStorage : NSObject<IZHTTPCookieStorage>

@property(nonatomic, readonly) NSDictionary *cookies;

@end


@interface NSDictionary (Obfuscate)

- (NSDictionary *)obfuscatedDictionaryForKeys:(NSSet *)obfuscateKeys;

@end

@interface NSArray (Obfuscate)

- (NSArray *)obfuscatedDictionaryForKeys:(NSSet *)obfuscateKeys;

@end

@interface UIApplication (Networking)

- (void)pushNetworkActivityIndicatorVisible;
- (void)popNetworkActivityIndicatorVisible;

@end

extern BOOL izNetworkActivityShouldUpdateStatusBarIndicator;
extern BOOL izNetworkDeveloperMode;

extern NSString *const IZNetworkHttpStatusCodeKey;

@interface NSError (SystemURLErrors)

@property (readonly) BOOL isURLError;
- (BOOL)isURLErrorWithCode:(NSInteger)code;

@property (readonly) BOOL isCancelledURLError;

+ (NSError *)urlErrorWithCode:(NSInteger)code;
+ (NSError *)urlCancelledError;

@end


NS_ASSUME_NONNULL_END
