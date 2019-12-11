//
//  UIViewController+Embedding.h
//  ContainmentTest
//
//  Created by Mattias Jähnke on 2012-10-30.
//  Copyright (c) 2012 Mattias Jähnke. All rights reserved.
//

@import UIKit;

@interface UIViewController (Embedding)

- (void)izEmbedViewController:(UIViewController *)viewController;
- (void)izEmbedViewController:(UIViewController *)viewController inView:(UIView *)view;
- (void)izEmbedViewController:(UIViewController *)viewController inView:(UIView *)view duration:(CGFloat)duration animationOptions:(UIViewAnimationOptions)animationOptions completion:(void(^)(BOOL finished))completion;
- (void)izReplaceViewController:(UIViewController *)viewController withViewController:(UIViewController *)newViewController;
- (void)izReplaceViewController:(UIViewController *)viewController withViewController:(UIViewController *)newViewController duration:(CGFloat)duration animationOptions:(UIViewAnimationOptions)animationOptions completion:(void(^)(BOOL finished))completion;
- (void)izDetatchViewControllerFromSuperview:(UIViewController*)viewController;

@end
