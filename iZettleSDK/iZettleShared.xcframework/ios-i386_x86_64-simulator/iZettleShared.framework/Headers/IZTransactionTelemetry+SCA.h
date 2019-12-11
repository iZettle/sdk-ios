//
//  IZTransactionTelemetry+SCA.h
//  iZettleShared
//
//  Created by Karl Johan Lemon-Drougge on 2019-10-03.
//  Copyright © 2019 iZettle. All rights reserved.
//

#import <iZettleShared/iZettleShared.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, IZSCATelemetryEvent) {
    IZSCATelemetryEventInitiatedSCATransaction,
    IZSCATelemetryEventCompletedSCATransaction,
    IZSCATelemetryEventFailedSCATransaction,
};

@interface IZTransactionTelemetry (SCA)

- (void)scaEventWithContext:(id<IZTelemetryContext>)context
                      event:(IZSCATelemetryEvent)event
          additionalPayload:(NSDictionary<NSString *, NSString *> *)additionalPayload;

@end

// Techincally not SCA related, can be generalized when analytics will be reviewed
extern NSString * const kIZTelemetryFailureReason;

extern NSString * const kIZTelemetryFailureReasonCancelledByUser;
extern NSString * const kIZTelemetryFailureReasonReaderTimeout;
extern NSString * const kIZTelemetryFailureReasonAborted;

extern NSString * const kIZTelemetryPaymentSessionId;
extern NSString * const kIZTelemetryCardEntryType;

NS_ASSUME_NONNULL_END
