//
//  UIWindow+Utilities.h
//  iZettle
//
//  Created by Måns Bernhardt on 2011-11-02.
//  Copyright (c) 2011 iZettle. All rights reserved.
//

@import UIKit;

@interface UIWindow (Utilities)


@property(nonatomic, readonly) BOOL isKeyboardVisible;
- (void)notifyWhenKeyboardVisibilityIsChanged:(void (^)(void))block;


+ (CGFloat)defaultKeyboardHeightForOrientation:(UIDeviceOrientation)orientation;


@end

@interface NSDictionary (KeyboardFrame)

- (BOOL)willUserInfoShowKeyboardForOrientation:(UIDeviceOrientation)orientation;

@end
