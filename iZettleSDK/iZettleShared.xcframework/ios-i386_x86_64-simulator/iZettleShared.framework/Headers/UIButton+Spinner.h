//
//  UIButton+Spinner.h
//  iZettleShared
//
//  Created by Jens Utbult on 2014-10-22.
//  Copyright (c) 2014 iZettle. All rights reserved.
//

@import UIKit;

@interface UIButton (Spinner)

- (void)startAnimateSpinner;
- (void)stopAnimateSpinner;
- (BOOL)isAnimating;

@end
