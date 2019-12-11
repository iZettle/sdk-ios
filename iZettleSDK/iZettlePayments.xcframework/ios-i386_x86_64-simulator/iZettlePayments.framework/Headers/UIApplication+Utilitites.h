//
//  UIApplication+Utilitites.h
//  iZettle
//
//  Created by Måns Bernhardt on 2011-06-21.
//  Copyright 2011 Babel Studios. All rights reserved.
//

@import UIKit;

typedef NS_ENUM(NSInteger, IZBuild) {
    IZBuildAppStore,
    IZBuildDevelopment,
    IZBuildSDK,
    IZBuildBeta,
};

@interface UIApplication (UIApplication_Utilitites)

+ (NSString *)izAppVersion;

+ (IZBuild)izBuildType;
+ (NSString *)izBuildName;

+ (NSString *)izSDKVersion;
+ (BOOL)izIsSDK;

+ (NSString *)izAPIKey;
+ (void)izSetAPIKey:(NSString *)apiKey;

+ (NSString *)izAPISourceApplication;
+ (void)izSetAPISourceApplication:(NSString *)sourceApplication;

@end
