//
//  CustomBarButtonItem.h
//  iZettleShared
//
//  Created by Mattias Jähnke on 2013-10-04.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import UIKit;

@class IZNavigationBar;

@interface CustomBarButtonItem : UIBarButtonItem

@property (nonatomic, readonly) CGFloat horizontalPadding;

- (void)styleWithNavigationBar:(IZNavigationBar *)navigationBar;

// Protected
- (UIView *)_customViewWithTitle:(NSString *)title target:(id)target action:(SEL)action;

@end

@interface DingbatBarButtonItem : CustomBarButtonItem

@end

@interface PlainTextButtonItem : CustomBarButtonItem

@end

@interface BackBarButtonItem : DingbatBarButtonItem

@end

@interface SpinnerBarButtonItem : CustomBarButtonItem

@property (nonatomic, readonly) UIActivityIndicatorView *spinner;

@end
