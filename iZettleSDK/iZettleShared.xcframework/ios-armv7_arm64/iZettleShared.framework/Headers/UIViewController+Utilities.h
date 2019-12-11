//
//  UIViewController+Utilities.h
//  iZettle
//
//  Created by Måns Bernhardt on 2012-10-31.
//  Copyright (c) 2012 iZettle. All rights reserved.
//

@import UIKit;


@interface UIViewController (Utilities)

@property (nonatomic, readonly) UIViewController *izRootViewController;
@property (nonatomic, readonly) UIInterfaceOrientation izInterfaceOrientation;
@property (nonatomic, readonly) BOOL izIsKeyboardVisible;


//- (void)izShowOverlayWithMessage:(NSString *)message spinner:(BOOL)showSpinner;
//- (void)izHideOverlay;
//- (void)izHideOverlayAnimated:(BOOL)animated;
//- (BOOL)izIsShowingOverlay;

@end
