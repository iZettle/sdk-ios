//
//  OverlayNotificationView.h
//  iZettle
//
//  Created by Mattias Jähnke on 2013-02-19.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import UIKit;

@interface OverlayNotificationView : UIView

@property (nonatomic, strong) UIView *parentView;
@property (nonatomic, assign) NSTimeInterval presentationTime;
@property (nonatomic, assign) CGFloat endAlpha;
@property (nonatomic, readwrite) NSString *dingbatIconString;
@property (nonatomic, readwrite) NSString *messageLabelText;

- (id)initWithDingbatString:(NSString*)dingbatString messageText:(NSString*)messageText crossedOver:(BOOL)crossedOver parentView:(UIView *)parentView;
- (id)initWithMessageText:(NSString *)text spinner:(BOOL)spinner parentView:(UIView *)parentView;
- (void)show; // Shows without blocking
- (void)showWithBlocking:(BOOL)blocking;
- (void)hide;
- (void)hideAnimated:(BOOL)animated;

// Present an overlay in window
+ (void)presentWithDingbatString:(NSString*)dingbatString message:(NSString*)message crossedOver:(BOOL)crossedOver;
+ (void)presentWithDingbatString:(NSString*)dingbatString message:(NSString*)message crossedOver:(BOOL)crossedOver inView:(UIView*)view;

@end

@interface UIView (OverlayNotificationView)

- (OverlayNotificationView *)presentOverlayWithMessage:(NSString *)message showSpinner:(BOOL)showSpinner blockUnderlyingView:(BOOL)blockUnderlyingView;

@end

@interface OverlayNotificationView (Shortcut)

+ (instancetype)overlayPleaseWaitInView:(UIView *)view;

@end
