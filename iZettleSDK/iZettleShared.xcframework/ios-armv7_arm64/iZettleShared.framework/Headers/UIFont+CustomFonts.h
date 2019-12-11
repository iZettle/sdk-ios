//
//  UIFont+CustomFonts.h
//  iZettle
//
//  Created by Nino Höglund on 2012-03-29.
//  Copyright (c) 2012 iZettle. All rights reserved.
//

@import UIKit;


@interface UIFont (CustomFonts)

+ (UIFont*)izLightFontOfSize:(CGFloat)size;
+ (UIFont*)izRegularFontOfSize:(CGFloat)size;
+ (UIFont*)izMediumFontOfSize:(CGFloat)size;
+ (UIFont*)izBoldFontOfSize:(CGFloat)size;

+ (UIFont*)izOcraFontOfSize:(CGFloat)size;
+ (UIFont*)izAmountFontOfSize:(CGFloat)size;

+ (UIFont*)izRegularDingbatFontOfSize:(CGFloat)size;
+ (UIFont*)izLightDingbatFontOfSize:(CGFloat)size;

@end
