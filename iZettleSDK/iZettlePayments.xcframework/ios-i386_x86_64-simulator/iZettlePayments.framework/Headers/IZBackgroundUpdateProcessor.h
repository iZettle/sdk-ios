// 
// Copyright © 2019 iZettle. All rights reserved.
// 

@import Foundation;

@class IZAccount;
@class DatecsReader;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, IZReaderRestartType) {
    IZReaderRestartTypeNow,
    IZReaderRestartTypeLater,
};

NS_SWIFT_NAME(BackgroundUpdateProcessorDelegate)
@protocol IZBackgroundUpdateProcessorDelegate <NSObject>

- (void)processorDidUpdateReader;
- (void)processorDidFailToUpdateReader:(NSError *)error;

@end

NS_SWIFT_NAME(BackgroundUpdateProcessor)
@interface IZBackgroundUpdateProcessor : NSObject

@property (nonatomic, weak) id<IZBackgroundUpdateProcessorDelegate> delegate;

- (instancetype)initWithAccount:(IZAccount *)account reader:(DatecsReader *)reader;
- (void)restartWithType:(IZReaderRestartType)restartType;

@end

NS_ASSUME_NONNULL_END
