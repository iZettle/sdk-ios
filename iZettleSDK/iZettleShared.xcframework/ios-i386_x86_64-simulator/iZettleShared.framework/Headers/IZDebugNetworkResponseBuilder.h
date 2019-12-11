//
//  IZDebugNetworkResponseBuilder.h
//  iZettleShared
//
//  Created by Nataliya Patsovska on 2018-07-25.
//  Copyright © 2018 iZettle. All rights reserved.
//

@import Foundation;
@class IZDebugNetworkResponse;

#ifdef DEBUG

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(DebugNetworkResponseBuilder)
@interface IZDebugNetworkResponseBuilder : NSObject

+ (nullable IZDebugNetworkResponse *)jsonResponseFromFileWithName:(NSString *)fileName
                                                         inBundle:(NSBundle *)bundle
                                                       statusCode:(NSInteger)statusCode
                                                            delay:(NSTimeInterval)delay NS_REFINED_FOR_SWIFT;

+ (nullable IZDebugNetworkResponse *)jsonResponseWithPayload:(id)payload
                                                  statusCode:(NSInteger)code
                                                       delay:(NSTimeInterval)delay NS_REFINED_FOR_SWIFT;

+ (IZDebugNetworkResponse *)jsonResponseWithData:(NSData *)data
                                      statusCode:(NSInteger)code
                                           delay:(NSTimeInterval)delay NS_REFINED_FOR_SWIFT;

+ (IZDebugNetworkResponse *)dataResponseWithData:(NSData *)data
                                      statusCode:(NSInteger)code
                                         headers:(NSDictionary<NSString*, NSString*> *)headers
                                           delay:(NSTimeInterval)delay NS_REFINED_FOR_SWIFT;

+ (IZDebugNetworkResponse *)errorResponseWithError:(NSError *)error
                                             delay:(NSTimeInterval)delay NS_REFINED_FOR_SWIFT;
@end

NS_ASSUME_NONNULL_END

#endif
