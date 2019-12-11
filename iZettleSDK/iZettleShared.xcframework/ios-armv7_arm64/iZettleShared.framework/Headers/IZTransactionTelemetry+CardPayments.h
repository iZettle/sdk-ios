// 
// Copyright © 2019 iZettle. All rights reserved.
// 

#import <Foundation/Foundation.h>
#import "IZTransactionTelemetry.h"

NS_ASSUME_NONNULL_BEGIN

/// Key representing unique payment UUID
extern NSString *const kIZCardPaymentUUIDKey;

extern NSString * const kIZTelemetryCardPaymentsSubdomain;

typedef NS_ENUM(NSUInteger, IZCardPaymentTelemetryEvent) {
    IZCardPaymentTelemetryEventStarted,
    IZCardPaymentTelemetryEventFinalized,
    IZCardPaymentTelemetryEventCancelled,
    IZCardPaymentTelemetryEventAborted,
    IZCardPaymentTelemetryEventTimeout,
};

typedef NS_ENUM(NSUInteger, IZTelemetryPinEntryEvent) {
    IZTelemetryPinEntryEventStarted,
    IZTelemetryPinEntryEventCompleted,
};

typedef NS_ENUM(NSUInteger, IZTelemetryCardEvent) {
    IZTelemetryCardEventCardPresented,
    IZTelemetryCardEventRemoveCardPresented,
    IZTelemetryCardEventCardRemoved,
};

@interface IZTransactionTelemetry (CardPaymentsTelemetry)

- (void)cardPaymentsEventWithContext:(id <IZTelemetryContext>)context
                               event:(IZCardPaymentTelemetryEvent)event;

- (void)cardPaymentsEventWithContext:(id <IZTelemetryContext>)context
                               event:(IZCardPaymentTelemetryEvent)event
                   additionalPayload:(NSDictionary<NSString *, NSString *> *)payload;

/// Send Pin Entry event
- (void)pinEntryEventWithContext:(id <IZTelemetryContext>)context event:(IZTelemetryPinEntryEvent)event;

/// Send event associated with physical card events
- (void)cardEventWithContext:(id <IZTelemetryContext>)context event:(IZTelemetryCardEvent)event;
@end

NS_ASSUME_NONNULL_END
