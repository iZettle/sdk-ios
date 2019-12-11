// 
// Copyright © 2019 iZettle. All rights reserved.
// 

@import Foundation;

@class DatecsReader;
@class IZAccount;

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(NecessaryBackgroundUpdateProcessorDelegate)
@protocol IZNecessaryBackgroundUpdateProcessorDelegate <NSObject>

- (void)processorDidUpdateProgress:(float)progress;
- (void)processorDidRestartReader;
- (void)processorDidUpdateReader;
- (void)processorDidFailToUpdateReader:(NSError *)error;

@end

NS_SWIFT_NAME(NecessaryBackgroundUpdateProcessorProtocol)
@protocol IZNecessaryBackgroundUpdateProcessorProtocol <NSObject>

@property (nonatomic, weak) id<IZNecessaryBackgroundUpdateProcessorDelegate> delegate;

- (instancetype)initWithAccount:(IZAccount *)account reader:(DatecsReader *)reader;
- (void)start;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_SWIFT_NAME(NecessaryBackgroundUpdateProcessor)
@interface IZNecessaryBackgroundUpdateProcessor : NSObject <IZNecessaryBackgroundUpdateProcessorProtocol>

@property (nonatomic, weak) id<IZNecessaryBackgroundUpdateProcessorDelegate> delegate;

- (instancetype)initWithAccount:(IZAccount *)account reader:(DatecsReader *)reader;
- (void)start;

@end

NS_ASSUME_NONNULL_END
