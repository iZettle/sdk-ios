//
//  AppDelegate.m
//  iZettle SDK Sample
//
//  Copyright (c) 2015 iZettle. All rights reserved.
//

#import "AppDelegate.h"
#import <iZettleSDK/iZettleSDK.h>

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    [[iZettleSDK shared] startWithAPIKey:@"demo-app-izorn"];
    return YES;
}

@end
