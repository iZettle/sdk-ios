//
//  IZLocationManager.h
//  iZettle
//
//  Created by Jens Utbult on 2011-11-16.
//  Copyright (c) 2011 iZettle. All rights reserved.
//

@import Foundation;
#import <CoreLocation/CoreLocation.h>
@import iZettleShared;

@class IZFuture;

NS_ASSUME_NONNULL_BEGIN

@interface IZLocationManager : NSObject<CLLocationManagerDelegate>

+ (IZLocationManager *)shared;

@property (assign, nonatomic, readonly, nullable) CLLocation *validLocation;

- (IZFuture *)requestAuthorization;
- (IZFuture<CLLocation *> *)waitForLocation; // return CLLocation
- (IZFuture *)verifyLocation;

- (void)startLocationMonitoringForClient:(id)client;
- (void)stopLocationMonitoringForClient:(id)client;

@end

@interface IZLocationManager (Utilities)

- (IZFuture<CLLocation *> *)waitForLocationWithTimeout:(NSTimeInterval)timeout; // return CLLocation? // nil if location is missing or timeout

@end



extern NSString *const LocationErrorDomain;

typedef NS_ERROR_ENUM(LocationErrorDomain, LocationErrorCode) {
    LocationErrorCodeLocationAuthorizationFailed,
    LocationErrorCodeInvalidLocationPlistSetup,
    LocationErrorCodeMissingLocation_Deprecated, 
};


@interface NSError (Location)

+ (NSString *)_locationErrorTitleForCode:(LocationErrorCode)code;
+ (NSString *)_locationErrorMessageWithCode:(LocationErrorCode)code;

+ (NSError *)locationErrorWithCode:(LocationErrorCode)code userInfo:(NSDictionary * _Nullable)info;

- (BOOL)isLocationErrorWithCode:(LocationErrorCode)code;

@end

NS_ASSUME_NONNULL_END
