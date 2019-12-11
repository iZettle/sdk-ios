//
//  LocalizedViewController.h
//  iZettle
//
//  Created by Måns Bernhardt on 2012-02-21.
//  Copyright (c) 2012 iZettle. All rights reserved.
//

@import UIKit;

extern NSString *const ActiveObserverRemoveAtViewWillDisappear;

@interface LocalizedViewController : UIViewController

@property (nonatomic, copy) NSString *screenName;
@property (nonatomic, assign) BOOL disableTracking;
@property (nonatomic, assign) BOOL disableAutomaticScrollsToTop;

/// A property that is used in preferredStatusBarStyle for LocalizedViewControllers without a class where the property cant be overridden.
@property (nonatomic, assign) int statusBarStyle;

- (void)sharedInit;

- (void)setNeedsLocalization;

- (void)addActiveObserverForName:(NSString *)name removeAt:(NSString *)removeAt object:(id)object usingBlock:(void(^)(NSNotification *note))block;
- (void)addActiveObserverForName:(NSString *)name removeAt:(NSString *)removeAt object:(id)object queue:(NSOperationQueue *)queue usingBlock:(void(^)(NSNotification *note))block;

@end


@interface UIViewController (LocalizedViewController)

- (void)keyboardWillShowInOrientation:(UIInterfaceOrientation)interfaceOrientation  rect:(CGRect)rect duration:(NSTimeInterval)duration;
- (void)keyboardDidShowInOrientation:(UIInterfaceOrientation)interfaceOrientation;

- (void)keyboardWillHideInOrientation:(UIInterfaceOrientation)interfaceOrientation rect:(CGRect)rect duration:(NSTimeInterval)duration;
- (void)keyboardDidHideInOrientation:(UIInterfaceOrientation)interfaceOrientation;

- (void)keyboardFrameWillChangeInOrientation:(UIInterfaceOrientation)interfaceOrientation willShow:(BOOL)willShow duration:(NSTimeInterval)duration;
- (void)keyboardFrameDidChangeInOrientation:(UIInterfaceOrientation)interfaceOrientation didShow:(BOOL)didShow;

@end

