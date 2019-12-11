// 
// Copyright © 2019 iZettle. All rights reserved.
// 

@import Foundation;

@class UIViewController;

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(NecessaryBackgroundUpdatePresentationDelegate)
@protocol IZNecessaryBackgroundUpdatePresentationDelegate <NSObject>

- (void)presentationWillAppear;
- (void)presentationCanceled;
- (void)presentationDone:(NSError * _Nullable) error;

@end

NS_SWIFT_NAME(NecessaryBackgroundUpdatePresentation)
@interface IZNecessaryBackgroundUpdatePresentation : NSObject

@property (nonatomic, weak) id<IZNecessaryBackgroundUpdatePresentationDelegate> delegate;
@property (nonatomic, strong, readonly) UIViewController *viewController;

+ (instancetype)pairingPresentation;
+ (instancetype)paymentPresentation;

- (void)presentProgress:(float)progress;
- (void)presentReaderRestarting;
- (void)presentSuccessfulUpdate;
- (void)presentFailedUpdate:(NSError *)error;

// --
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
