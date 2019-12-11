// 
// Copyright © 2019 iZettle. All rights reserved.
// 

#import <iZettleShared/iZettleShared.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, IZGratuityTrackingEvent) {
    IZGratuityTrackingEventStarted,
    IZGratuityTrackingEventAborted,
    IZGratuityTrackingEventCompleted,
    IZGratuityTrackingEventUserSkipped,
    IZGratuityTrackingEventAmountTooHigh,
    IZGratuityTrackingEventAmountTooLow,
    IZGratuityTrackingEventRetried,
};

@interface IZTransactionTelemetry (Gratuity)

- (void)gratuityEventWithContext:(id <IZTelemetryContext>)context
                           event:(IZGratuityTrackingEvent)event
               additionalPayload:(NSDictionary<NSString *, NSString *> *)additionalPayload;

- (void)gratuityEventWithContext:(id <IZTelemetryContext>)context
                           event:(IZGratuityTrackingEvent)event;

@end

NS_ASSUME_NONNULL_END
