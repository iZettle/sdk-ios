// 
// Copyright © 2019 iZettle. All rights reserved.
// 

#import "IZNecessaryBackgroundUpdateProcessor.h"
@import Foundation;

@class IZNecessaryBackgroundUpdatePresentation;

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(NecessaryBackgroundUpdateFlow)
@interface IZNecessaryBackgroundUpdateFlow : NSObject

- (instancetype)initWithPresentation:(IZNecessaryBackgroundUpdatePresentation *)presentation
                           processor:(id <IZNecessaryBackgroundUpdateProcessorProtocol>)processor;

- (void)update:(void(^)(NSError * _Nullable error))completion;

// --
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
