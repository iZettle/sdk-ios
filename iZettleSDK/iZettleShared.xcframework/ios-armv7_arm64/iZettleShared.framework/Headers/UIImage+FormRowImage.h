//
//  UIImage+FormRowImage.h
//  iZettleShared
//
//  Created by Mattias Jähnke on 2013-05-21.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import UIKit;

@interface UIImage (FormRowImage)

- (UIImage *)imageForRowIsFirst:(BOOL)isFirst isLast:(BOOL)isLast;
- (UIImage *)firstRowImage;
- (UIImage *)bothRowImage;
- (UIImage *)middleRowImage;
- (UIImage *)lastRowImage;

- (UIImage *)formBackgroundWithRect:(CGRect)rect withResizeInsets:(UIEdgeInsets)insets;

@end
