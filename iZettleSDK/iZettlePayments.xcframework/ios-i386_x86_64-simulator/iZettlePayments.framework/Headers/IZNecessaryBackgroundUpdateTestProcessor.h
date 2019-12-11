// 
// Copyright © 2019 iZettle. All rights reserved.
// 

@import Foundation;
#import "IZNecessaryBackgroundUpdateProcessor.h"

NS_ASSUME_NONNULL_BEGIN

@interface IZNecessaryBackgroundUpdateTestProcessor : NSObject <IZNecessaryBackgroundUpdateProcessorProtocol>

@property (nonatomic, weak) id<IZNecessaryBackgroundUpdateProcessorDelegate> delegate;

- (instancetype)initWithAccount:(IZAccount *)account reader:(DatecsReader *)reader;
- (void)start;

@end

NS_ASSUME_NONNULL_END
