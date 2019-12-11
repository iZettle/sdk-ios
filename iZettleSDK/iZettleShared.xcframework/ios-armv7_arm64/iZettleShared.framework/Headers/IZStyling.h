//
//  Copyright (c) 2019 iZettle. All rights reserved.
//

@import UIKit;
@protocol IZColorThemeProvider;

NS_ASSUME_NONNULL_BEGIN

@interface IZStyling: NSObject

+ (instancetype)sharedInstance;

@property (nonatomic, strong) id<IZColorThemeProvider> colorThemeProvider;

@end

NS_ASSUME_NONNULL_END
