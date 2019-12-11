//
//  UpdateManager.h
//  iZettlePayments
//
//  Created by Andrei Valkovskii on 2019-01-18.
//  Copyright © 2019 iZettle. All rights reserved.
//

@import Foundation;

@class IZReaderNetworkContext;
@class DatecsReaderQueue;

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(BackgoundUpdateManagerDelegate)
@protocol IZBackgoundUpdateManagerDelegate <NSObject>

- (void)updateManagerDidUpdateProgress:(float)progress;
- (void)updateManagerDidSuspendProgress:(float)progress;
- (void)updateManagerDidFinishUpdate:(NSError * _Nullable)error;

@end

NS_SWIFT_NAME(BackgroundUpdateManager)
@interface IZBackgroundUpdateManager : NSObject

- (instancetype)initWithReader:(DatecsReaderQueue *)readerQueue
                networkContext:(IZReaderNetworkContext *)networkContext
                      delegate:(id<IZBackgoundUpdateManagerDelegate>)delegate;

- (void)startUpdate;
- (void)suspend:(BOOL)suspend;
- (void)cancelUpdate;

// --

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end


NS_ASSUME_NONNULL_END
