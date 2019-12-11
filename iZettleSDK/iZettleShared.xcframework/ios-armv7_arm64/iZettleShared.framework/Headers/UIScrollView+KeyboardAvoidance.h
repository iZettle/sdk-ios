//
//  UIScrollView+KeyboardAvoidance.h
//  iZettleShared
//
//  Created by Mattias Jähnke on 2013-05-10.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import UIKit;

@interface UIScrollView (KeyboardAvoidance)

- (void)izRegisterForKeyboardAvoidance;
- (void)izUnregisterKeyboardAvoidance;

- (void)izAdjustBottomInsetsForViewport:(CGRect)aViewport withEdgeInsets:(UIEdgeInsets)edgeInsets;
- (void)izScrollToRect:(CGRect)rect inView:(UIView *)view inViewport:(CGRect)aViewport;

- (void)izScrollToRevealFirstResponder; // Helper - calls izScrollToRect:inView:inViewport with the first responder and current viewport
- (UIView *)izFirstResponder;

@end