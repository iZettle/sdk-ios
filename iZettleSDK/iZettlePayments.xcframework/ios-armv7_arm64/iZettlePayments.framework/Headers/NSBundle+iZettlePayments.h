//
//  NSBundle+iZettlePayments.h
//  iZettleSDK
//
//  Created by Måns Bernhardt on 2013-04-10.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import UIKit;

@interface NSBundle (iZettlePayments)

+ (NSBundle *)iZettlePaymentsBundle;

@end


@interface UIImage (iZettlePayments)

+ (UIImage *)iZettlePaymentsImageNamed:(NSString *)name;

@end
