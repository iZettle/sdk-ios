// 
// Copyright © 2019 iZettle. All rights reserved.
// 

#import <iZettleShared/iZettleShared.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, IZRepeatPaymentsTelemetryEvent) {
    IZRepeatPaymentsTelemetryEventStarted,
    IZRepeatPaymentsTelemetryEventFinalized,
};

@interface IZTransactionTelemetry (RepeatPayments)

- (void)repeatPaymentsEventWithContext:(id <IZTelemetryContext>)context
                                 event:(IZRepeatPaymentsTelemetryEvent)event
                     additionalPayload:(NSDictionary<NSString *, NSString *> *)payload;

@end

NS_ASSUME_NONNULL_END
