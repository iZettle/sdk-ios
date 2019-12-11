// 
// Copyright © 2019 iZettle. All rights reserved.
// 

@import Foundation;

@class IZBackgroundUpdatePresentation;
@class IZBackgroundUpdateProcessor;

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(BackgroundUpdateFlow)
@interface IZBackgroundUpdateFlow : NSObject

- (instancetype)initWithPresentation:(IZBackgroundUpdatePresentation *)presentation
                           processor:(IZBackgroundUpdateProcessor *)processor;

- (void)update:(void(^)(NSError * _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
