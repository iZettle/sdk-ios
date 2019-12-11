//
//  ViewController.h
//  iZettleShared
//
//  Created by Mattias Jähnke on 2014-12-12.
//  Copyright (c) 2014 iZettle. All rights reserved.
//

@import UIKit;

@class IZFuture;

@interface UIViewController (iZettlePresentationUtil)

// Will wrap the viewController in a new IZNavigationController (and return the navigation controller)
- (UIViewController *)izPresentModal:(UIViewController *)viewController wrapInNavigationController:(BOOL)wrapInNavigationController completion:(dispatch_block_t)completion;

// Can be called from either the presenting viewcontroller of the presented viewcontroller
- (void)izDismissModal;
- (void)izDismissModalCompletion:(dispatch_block_t)completion;

@end

@interface UINavigationController (iZettlePresentationUtil)

// Push viewController with flip animation
- (void)pushFlipViewController:(UIViewController *)viewController;

// Pop the topViewController with a flip animation
- (void)popFlipViewController;

- (void)popFlipToRootController;

@end

@interface UIViewController (OperationPresentation)

- (IZFuture *)presentOperationFlowUsingFunction:(IZFuture *(^)(UINavigationController *nc))function;

@end
