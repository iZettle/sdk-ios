//
//  Herd.h
//  iZettleShared
//
//  Created by Mattias Jähnke on 2015-09-10.
//  Copyright © 2015 iZettle. All rights reserved.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

@interface Herd : NSObject

/*!
 Initialize this Herd with a given endpoint
 */
- (id)initWithEndpoint:(NSURL *)endpoint;

/*!
 Herd backend endpoint
 */
@property (copy) NSURL *endpoint;

/*!
 Toggle logging for debugging
 */
@property (assign) BOOL verbose;

/*!
 Report to Herd
 */
- (void)reportAttemptWithType:(NSString *)type
                      success:(BOOL)success
                        start:(NSDate *)start
                          end:(NSDate *)end
                         meta:(NSDictionary * _Nullable)meta;

/*!
 Retrieve the status json object from Herd
 */
- (void)statusWithCompletion:(void(^)(NSDictionary * _Nullable payload, NSError * _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
