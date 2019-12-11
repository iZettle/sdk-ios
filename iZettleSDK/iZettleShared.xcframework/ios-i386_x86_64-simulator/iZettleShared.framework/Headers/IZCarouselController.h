//
//  IZCarouselController.h
//  iZettleShared
//
//  Created by Jens Utbult on 2015-04-29.
//  Copyright (c) 2015 iZettle. All rights reserved.
//

@import UIKit;

NS_ASSUME_NONNULL_BEGIN

@protocol IZCarouselPageProtocol <NSObject>

- (void)izPageDidAppear;
- (void)izPageDidDisappear;
- (void)izFadeOut:(CGFloat)fade;
- (void)izFadeIn:(CGFloat)fade;

@end

@interface IZCarouselController : UIViewController



@property (nonatomic, readonly) NSArray<UIView<IZCarouselPageProtocol> *> *pages;

- (instancetype)initWithPages:(NSArray<UIView<IZCarouselPageProtocol> *> *)pages;

@end

NS_ASSUME_NONNULL_END
