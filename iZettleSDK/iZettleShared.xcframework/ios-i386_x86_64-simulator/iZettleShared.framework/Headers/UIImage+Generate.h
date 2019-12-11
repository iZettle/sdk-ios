//
//  UIImage+Generate.h
//  iZettleShared
//
//  Created by Mattias Jähnke on 2013-04-29.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import UIKit;

@interface UIImage (Generate)

+ (UIImage *)imageWithFillColor:(UIColor *)fillColor borderColor:(UIColor *)borderColor backgroundColor:(UIColor *)backgroundColor cornerRadius:(CGFloat)cornerRadius corners:(UIRectCorner)corners;
+ (UIImage *)imageWithFillColor:(UIColor *)fillColor borderColor:(UIColor *)borderColor backgroundColor:(UIColor *)backgroundColor cornerRadius:(CGFloat)cornerRadius;
+ (UIImage *)imageWithFillColor:(UIColor *)fillColor borderColor:(UIColor *)borderColor backgroundColor:(UIColor *)backgroundColor cornerRadius:(CGFloat)cornerRadius straightAreaLength:(CGFloat)straightAreaLength corners:(UIRectCorner)corners;
+ (UIImage *)imageWithFillColor:(UIColor *)fillColor cornerRadius:(CGFloat)cornerRadius;

+ (UIImage *)imageWithFillColor:(UIColor *)fillColor
                    borderColor:(UIColor *)borderColor
                backgroundColor:(UIColor *)backgroundColor
                   cornerRadius:(CGFloat)cornerRadius
                           rect:(CGRect)rect
                        corners:(UIRectCorner)corners
                    borderInset:(CGSize)borderInset;

+ (UIImage *)imageNamed:(NSString *)name withBackgroundColor:(UIColor *)backgroundColor;
+ (UIImage *)imageWithColor:(UIColor *)color;
+ (UIImage *)imageFromDingbatString:(NSString *)dingbatString fontSize:(CGFloat)size margin:(CGFloat)margin backgroundColor:(UIColor *)backgroundColor dingbatColor:(UIColor *)dingbatColor;
+ (UIImage *)imageFromDingbatString:(NSString *)dingbatString margin:(CGFloat)margin backgroundColor:(UIColor *)backgroundColor dingbatColor:(UIColor *)dingbatColor dingbatFont:(UIFont *)dingbatFont;
+ (UIImage *)imageWithFillColor:(UIColor *)fillColor borderColor:(UIColor *)borderColor backgroundColor:(UIColor *)backgroundColor cornerRadius:(CGFloat)cornerRadius rect:(CGRect)rect corners:(UIRectCorner)corners;

+ (UIImage *)izFullScreenSnapshotImage;

@end
