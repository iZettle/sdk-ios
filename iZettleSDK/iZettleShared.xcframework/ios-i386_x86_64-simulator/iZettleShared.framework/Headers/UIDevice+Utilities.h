//
//  UIDevice+Utilities.h
//  iZettle
//
//  Created by Nino Höglund on 2011-10-19.
//  Copyright (c) 2011 Babel Studios. All rights reserved.
//

@import UIKit;

@interface UIDevice (Utilities)

+ (BOOL)isCurrentlyRegularSized;
+ (BOOL)isCurrentlyCompactSized;
+ (BOOL)isCurrentlyCompactAndTallSized;

+ (BOOL)isPriorToIOS9;
+ (BOOL)isPriorToIOS10;
+ (BOOL)isPriorToIOS11;
+ (BOOL)isGreaterThanIOS9;

+ (BOOL)isRetina;
+ (CGFloat)scale;
+ (CGFloat)iphoneSizeFactor;

@property (nonatomic, copy, readonly) NSString *modelCode;
@property (nonatomic, copy, readonly) NSString *modelName;
@property (nonatomic, copy, readonly) NSString *modelCodeAndName;
@property (nonatomic, copy, readonly) NSString *idiomString;
@property (nonatomic, copy, readonly) NSString *izUDID;

+ (CGFloat)osVersion;

+ (BOOL)isAttachedToDebugger;

/// Returns true if the app is the production version downloaded from Appstore. Note that this will return false for Testflight builds.
+ (BOOL)isRunningInAppstore;

// These are all deprecated. Use size class based [UIDevice isCurrently*] instead.
+ (BOOL)isIphone __attribute__ ((deprecated));
+ (BOOL)isIpad __attribute__ ((deprecated));
+ (BOOL)isLargeIpad __attribute__ ((deprecated));
+ (BOOL)izIsTall __attribute__ ((deprecated));
+ (BOOL)isNarrowIphone __attribute__ ((deprecated));

@end
