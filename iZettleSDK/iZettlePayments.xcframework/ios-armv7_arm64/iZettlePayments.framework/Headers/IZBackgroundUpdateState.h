// 
// Copyright © 2019 iZettle. All rights reserved.
// 

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, IZBackgroundUpdateStatus) {
    IZBackgroundUpdateStatusUpdating  = 1,
    IZBackgroundUpdateStatusSuspended = 2,
    IZBackgroundUpdateStatusFinished  = 3,
    IZBackgroundUpdateStatusUpToDate  = 4,
    IZBackgroundUpdateStatusFailed    = 5,
};

NS_SWIFT_NAME(BackgroundUpdateState)
@interface IZBackgroundUpdateState : NSObject

@property (nonatomic, assign, readonly) IZBackgroundUpdateStatus status;
/// Value that indicates update progress. Range is 0 ... 1
@property (nonatomic, assign, readonly) float progress;

+ (instancetype)updateStateUpdating:(float)progress NS_SWIFT_NAME(updating(progress:));
+ (instancetype)updateStateSuspended:(float)progress NS_SWIFT_NAME(suspended(progress:));
+ (instancetype)updateStateFinished NS_SWIFT_NAME(finished());
+ (instancetype)updateStateFailed NS_SWIFT_NAME(failed());
+ (instancetype)updateStateUpToDate NS_SWIFT_NAME(upToDate());

// --
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
