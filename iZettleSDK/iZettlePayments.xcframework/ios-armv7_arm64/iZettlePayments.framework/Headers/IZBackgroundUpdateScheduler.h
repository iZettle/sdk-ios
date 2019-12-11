// 
// Copyright © 2019 iZettle. All rights reserved.
// 

@import Foundation;
@class IZCardReader;

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(BackgroundUpdateScheduler)
@interface IZBackgroundUpdateScheduler : NSObject

@property (nonatomic, assign) NSTimeInterval delay;

- (instancetype)initWithNotificationCenter:(NSNotificationCenter *)notificationCenter;

- (void)scheduleWithReaders:(NSArray<IZCardReader *> *)readers;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

FOUNDATION_EXPORT NSNotificationName const IZReaderUpdateReadyNotification
    NS_SWIFT_NAME(BackgroundUpdateScheduler.updateReady);

NS_ASSUME_NONNULL_END
