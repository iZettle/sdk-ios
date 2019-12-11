//
//  DatecsReader.h
//  iZettleStorePurchase
//
//  Created by Mattias Jähnke on 2015-09-24.
//  Copyright © 2015 iZettle. All rights reserved.
//

#import "IZCardReader.h"
#import "IZPeripheralLink.h"

NS_ASSUME_NONNULL_BEGIN

@class IZAccessoryService;
@class IZEmvMessage;
@class IZBackgroundUpdateState;

@interface DatecsReaderQueue : IZCardReaderQueue

/// Signals each time reader emits an event
@property (nonatomic, strong, readonly) IZSignal<NSData *> *eventSignal;

- (IZFuture *)sendFrameData:(NSData *)frame
                    timeout:(NSTimeInterval)timeout
                 retryCount:(NSUInteger)retryCount;

- (IZFuture *)sendFrameData:(NSData *)frame
                    timeout:(NSTimeInterval)timeout;

- (IZFuture<IZEmvMessage *> *)executeConfigurationNamedCommandBlock;
- (IZFuture<IZEmvMessage *> *)executeSoftwareUpdateNamedCommandBlock;

@end

extern NSString *const kDatecsMfiProtocol;

//! The name of the reader.
extern NSString * const DatecsReaderName;

@interface DatecsReader : IZCardReader <IZPeripheralLinkDelegate>

@property(nonatomic, assign) BOOL supportsBackgroundUpdate;
@property (nonatomic, assign, readonly, getter=isNecessaryUpdate) BOOL necessaryUpdate;
@property (nonatomic, strong, readonly, nullable) IZBackgroundUpdateState *backgroundUpdateState NS_REFINED_FOR_SWIFT;
@property (nonatomic, strong, readonly) IZSignal<IZBackgroundUpdateState *> *backgroundUpdateStateSignal NS_REFINED_FOR_SWIFT;

@property (nonatomic, weak) id<IZTelemetryContext> telemetry;

@property (nonatomic, strong, readonly) IZSignal<NSNumber *> *dockedStatusSignal NS_REFINED_FOR_SWIFT;

- (instancetype)initWithAccessoryService:(IZAccessoryService *)service networkContext:(IZReaderNetworkContext *)networkContext;
- (instancetype)initWithPeripheralLink:(id<IZPeripheralLink>)peripheralLink networkContext:(IZReaderNetworkContext *)networkContext;

// TODO: Move to DatecsReaderQueue
@property (readonly) NSInteger nextSequenceNumber;

// Hack for logging
- (void)startLogging;
- (void)stopLogging;

// Echo command
- (IZFuture<NSData *> *)echo:(NSData *)payload;

- (IZFuture *)suspendUpdateIfNeeded;
- (IZFuture *)resumeUpdateIfNeeded;

- (void)restart;

@end

NS_ASSUME_NONNULL_END
