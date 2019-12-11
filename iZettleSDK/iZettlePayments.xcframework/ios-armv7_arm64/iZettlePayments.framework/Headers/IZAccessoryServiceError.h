//
//  IZAccessoryServiceError.h
//  iZettlePayments
//
//  Created by Andrei Valkovskii on 2018-05-08.
//  Copyright © 2018 iZettle. All rights reserved.
//

#import <Foundation/Foundation.h>

FOUNDATION_EXPORT NSErrorDomain _Nonnull IZAccessoryServiceErrorDomain;

typedef NS_ERROR_ENUM(IZAccessoryServiceErrorDomain, IZAccessoryServiceErrorCode) {
    IZAccessoryServiceErrorCodeConnectionProblem,
    IZAccessoryServiceErrorCodeTimeout,
    IZAccessoryServiceErrorBadSession
} NS_SWIFT_NAME(AccessoryServiceErrorCode);

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(AccessoryServiceError)
@interface IZAccessoryServiceError : NSError

+ (instancetype)errorBadConnection;
+ (instancetype)errorConnectionTimeout;
+ (instancetype)errorBadSession;

@end

NS_ASSUME_NONNULL_END
