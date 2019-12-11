// 
// Copyright © 2019 iZettle. All rights reserved.
// 

#import <iZettleShared/iZettleShared.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, IZAccountTelemetryEvent) {
    IZAccountTelemetryEventLoggedIn,
    IZAccountTelemetryEventSwitchedUser,
    IZAccountTelemetryEventLoggedOut,
};

@interface IZTelemetry (Account)

+ (void)accountEventWithContext:(id <IZTelemetryContext>)context event:(IZAccountTelemetryEvent)event;

@end

NS_ASSUME_NONNULL_END
