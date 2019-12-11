// 
// Copyright © 2019 iZettle. All rights reserved.
// 

@import Foundation;

@class UINavigationController;

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(BackgroundUpdatePresentationDelegate)
@protocol IZBackgroundUpdatePresentationDelegate <NSObject>

- (void)presentationCanceled;
- (void)presentationRequestedRestart;
- (void)presentationDone:(NSError * _Nullable)error;

@end

NS_SWIFT_NAME(BackgroundUpdatePresentation)
@interface IZBackgroundUpdatePresentation : NSObject

@property (nonatomic, strong, readonly) UINavigationController *viewController;
@property (nonatomic, weak) id<IZBackgroundUpdatePresentationDelegate> delegate;

- (instancetype)initWithReaderIconName:(NSString *)iconName;

- (void)presentReaderRestarting;
- (void)presentSuccessfulUpdate;
- (void)presentFailedUpdate:(NSError *)error;

@end

NS_ASSUME_NONNULL_END
