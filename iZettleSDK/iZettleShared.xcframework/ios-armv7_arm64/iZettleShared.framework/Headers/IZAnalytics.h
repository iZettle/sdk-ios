//
//  Analytics.h
//  iZettleShared
//
//  Created by Måns Bernhardt on 2013-04-09.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import Foundation;

typedef enum {
    AnalyticsLevelInfo,
    AnalyticsLevelWarning,
    AnalyticsLevelFatal
} AnalyticsLevel;

// Categories
extern NSString *const kAnalyticsEventCategoryUIAction;

// Actions
extern NSString *const kAnalyticsEventActionButtonPressed;

@protocol IZAnalytics <NSObject>

// Defaults - system determined levels
- (void)visit:(NSString *)place;

// Track custom event to an unspecified target
- (void)eventWithCategory:(NSString *)category action:(NSString *)action;
- (void)eventWithCategory:(NSString *)category action:(NSString *)action label:(NSString *)label value:(NSNumber *)value;

// Track a custom event to a specified target. The event is consumed by a target.
- (void)eventWithTarget:(NSString *)target category:(NSString *)category action:(NSString *)action label:(NSString *)label value:(NSNumber *)value;
- (void)log:(id)message;            // Will do a log with infoLevel
- (void)warn:(id)message;           // Will do a log with warningLevel

// Customizable levels
- (void)log:(id)message withLevel:(AnalyticsLevel)level;

@end

id<IZAnalytics> sharedAnalytics(void);
void setSharedAnalytics(id<IZAnalytics> sharedAnalytics);
