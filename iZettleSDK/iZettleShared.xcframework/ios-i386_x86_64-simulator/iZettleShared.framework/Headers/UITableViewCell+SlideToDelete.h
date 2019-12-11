//
//  UITableViewCell+SlideToDelete.h
//  iZettle
//
//  Created by Mattias Jähnke on 2014-10-15.
//  Copyright (c) 2014 iZettle. All rights reserved.
//

@import UIKit;

@interface UITableViewCell (SlideToDelete)
- (void)izInstallSlideWithSlideContainer:(UIView *)slideContainer text:(NSString *)text deletionBlock:(dispatch_block_t)deletionBlock;
- (void)izUninstallSlide;
- (BOOL)izHasSlideInstalled;
@end
