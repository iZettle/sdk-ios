//
//  UIBarButtonItem+Utilities.h
//  iZettleShared
//
//  Created by Måns Bernhardt on 2013-05-16.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import UIKit;


@interface UIBarButtonItem (action)

@property (nonatomic, copy) dispatch_block_t actionBlock;

+ (instancetype)barButtonWithSystemItem:(UIBarButtonSystemItem)systemItem action:(dispatch_block_t)block;
+ (instancetype)barButtonWithTitle:(NSString *)title action:(dispatch_block_t)action;

@end
