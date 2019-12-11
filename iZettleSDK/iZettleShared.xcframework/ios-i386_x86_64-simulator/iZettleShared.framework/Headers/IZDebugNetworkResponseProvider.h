//
//  IZDebugNetworkResponseProvider.h
//  iZettleShared
//
//  Created by Nataliya Patsovska on 2018-07-25.
//  Copyright © 2018 iZettle. All rights reserved.
//

@import Foundation;
@protocol IZDisposable;

#ifdef DEBUG

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(DebugNetworkResponse)
@interface IZDebugNetworkResponse: NSObject

@property (assign, nonatomic) NSInteger statusCode;
@property (strong, nonatomic) NSData *data;
@property (assign, nonatomic) NSTimeInterval delay;
@property (strong, nonatomic, nullable) NSDictionary<NSString*, NSString*>* httpHeaders;
@property (strong, nonatomic, nullable) NSError* error;

@end

NS_SWIFT_NAME(DebugNetworkResponseTest)
typedef BOOL (^IZDebugNetworkResponseTest)(NSURLRequest* request);

NS_SWIFT_NAME(DebugNetworkResponseGetter)
typedef IZDebugNetworkResponse *_Nullable(^IZDebugNetworkResponseGetter)(NSURLRequest* request);

NS_SWIFT_NAME(DebugNetworkResponseProvider)
@interface IZDebugNetworkResponseProvider: NSObject

+ (instancetype)sharedInstance;

- (id<IZDisposable>)registerResponseGetter:(IZDebugNetworkResponseGetter)responseGetter
                     forRequestPassingTest:(IZDebugNetworkResponseTest)test;

- (BOOL)hasResponseForRequest:(NSURLRequest *)request;

- (nullable IZDebugNetworkResponse *)responseForRequest:(NSURLRequest *)request;

@end

NS_ASSUME_NONNULL_END

#endif
