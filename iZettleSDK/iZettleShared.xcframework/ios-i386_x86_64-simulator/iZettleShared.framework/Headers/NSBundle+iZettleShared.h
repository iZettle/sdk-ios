//
//  NSBundle+iZettleShared.h
//  iZettleSDK
//
//  Created by Måns Bernhardt on 2013-04-10.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import UIKit;

@interface NSBundle (iZettleShared)

+ (NSBundle *)iZettleSharedBundle;

@end


@interface UIImage (iZettleShared)

+ (UIImage *)iZettleSharedImageNamed:(NSString *)name;

@end

#ifdef DEBUG
@interface UIApplication (iZettleShared)
+ (void)forceCrash;
+ (BOOL)izIsRunningUnitTests;
@end
#endif
