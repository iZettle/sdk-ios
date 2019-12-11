//
//  UIAlertView+QuickAlert.h
//  iZettleShared
//
//  Created by Mattias Jähnke on 2013-08-26.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import UIKit;
#import "IZFuture.h"

NS_ASSUME_NONNULL_BEGIN

typedef void (^QuickAlertCompletionBlock) (NSInteger selectedIndex, BOOL didCancel);
typedef void (^InputQuickAlertCompletionBlock) (NSInteger selectedIndex, BOOL didCancel, NSString *textFieldText);

//@interface UIAlertView (QuickAlert)
//
//+ (UIAlertView *)showAlertWithTitle:(NSString *)title message:(NSString *)message cancelButtonTitle:(NSString *)aCancelTitle otherButtonTitles:(NSArray *)otherButtonTitles completion:(QuickAlertCompletionBlock)completion;
//+ (UIAlertView *)showInputAlertWithTitle:(NSString *)title message:(NSString *)message cancelButtonTitle:(NSString *)aCancelTitle otherButtonTitles:(NSArray *)otherButtonTitles completion:(InputQuickAlertCompletionBlock)completion;
//
//@end

// Temp helper to ease transition, will present on rootController
@interface UIAlertController (QuickAlert)

// Returns selected index
+ (IZFuture<NSNumber *> *)showAlertWithTitle:(NSString * _Nullable)title message:(NSString * _Nullable)message cancelButtonTitle:(NSString * _Nullable)aCancelTitle otherButtonTitles:(NSArray * _Nullable)otherButtonTitles; // return NSInteger selectedIndex or NSError if user aborts.

+ (IZFuture<NSNumber *> *)showAlertWithError:(NSError *)error title:(NSString *)title;  // return future aborted with error
+ (IZFuture<NSNumber *> *)showAlertWithError:(NSError *)error; // return future aborted with error
+ (IZFuture<NSNumber *> *)showAlertWithRetryAndError:(NSError *)error; // won't abort with error if retry is pressed.

@end


@interface IZFuture (Alert)

- (IZFuture *)catchAndDisplayErrorOnViewController:(UIViewController *)viewController;

@end

@interface UIViewController (Alert)

- (IZFuture<NSNumber *> *)showAlertWithTitle:(NSString * _Nullable)title message:(NSString * _Nullable)message cancelButtonTitle:(NSString * _Nullable)aCancelTitle otherButtonTitles:(NSArray * _Nullable)otherButtonTitles; // return NSInteger selectedIndex or NSError if user aborts.

- (IZFuture<NSNumber *> *)showAlertWithError:(NSError *)error; // return future aborted with error
- (IZFuture *)showAlertWithError:(NSError *)error title:(NSString *)title;
- (IZFuture<NSNumber *> *)showAlertWithRetryAndError:(NSError *)error; // won't abort with error if retry is pressed.

@end

NS_ASSUME_NONNULL_END
