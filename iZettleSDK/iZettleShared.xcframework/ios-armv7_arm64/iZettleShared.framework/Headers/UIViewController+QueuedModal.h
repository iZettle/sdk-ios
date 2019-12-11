//
//  ViewController+QueuedModal.h
//  ModalTesting
//
//  Created by Mattias Jähnke on 2012-10-24.
//  Copyright (c) 2012 Mattias Jähnke. All rights reserved.
//

@import UIKit;

extern NSString *const WillPresentQueuedModalNotification;
extern NSString *const DidPresentQueuedModalNotification;

extern NSString *const WillDismissQueuedModalNotification;
extern NSString *const DidDismissQueuedModalNotification;

typedef NS_ENUM(NSInteger, QueuedModalAnimationType) {
    QueuedModalAnimationTypeDefault, // zoom with bounce??
    QueuedModalAnimationTypeNone,
    QueuedModalAnimationTypeFade,
    QueuedModalAnimationTypeSlideUp,
    QueuedModalAnimationTypeSlideDown,
    QueuedModalAnimationTypeSlideLeft,
    QueuedModalAnimationTypeSlideRight,
    
    // Scale animations
    QueuedModalAnimationScale = 1<<16,
    QueuedModalAnimationAddBounce = 1<<17,
    QueuedModalAnimationRestrictToVertical = 1<<18,
    QueuedModalAnimationRestrictToHorizontal = 1<<19,

    QueuedModalAnimationTypeZoom = QueuedModalAnimationScale,
    QueuedModalAnimationTypeZoomWithBounce = QueuedModalAnimationScale|QueuedModalAnimationAddBounce,

    QueuedModalAnimationTypeScaleHorizontally = QueuedModalAnimationScale|QueuedModalAnimationRestrictToHorizontal,
    QueuedModalAnimationTypeScaleHorizontallyWithBounce = QueuedModalAnimationScale|QueuedModalAnimationAddBounce|QueuedModalAnimationRestrictToHorizontal,
    QueuedModalAnimationTypeScaleVertically = QueuedModalAnimationScale|QueuedModalAnimationRestrictToVertical,
    QueuedModalAnimationTypeScaleVerticallyWithBounce = QueuedModalAnimationScale|QueuedModalAnimationAddBounce|QueuedModalAnimationRestrictToVertical,
};

typedef NS_ENUM(NSInteger, QueuedModalPresentationPriority) {
    QueuedModalPresentationPriorityGlobal,
    QueuedModalPresentationPriorityNormal,
    QueuedModalPresentationPriorityCount, // Should not be used as priority
};

typedef NS_ENUM(NSInteger, QueuedModalOverlayType) {
    QueuedModalOverlayTypeAlphaColor,
    QueuedModalOverlayTypeTransparent,
};

typedef void(^ModalCompletionBlock)(void);

@class IZFuture;

@interface UIViewController (QueuedModal)

+ (void)setDefaultQueuedModalAnimation:(QueuedModalAnimationType)animation;
+ (QueuedModalAnimationType)defaultQueuedModalAnimation;

// This method puts a view contoller in the queue and will be presented as soon as possible - once the view controllers before it are dismissed, or immediately if the queue is empty
- (void)presentQueuedModal:(UIViewController *)modalViewController completion:(ModalCompletionBlock)completion;


- (void)globallyPresentQueuedModal:(UIViewController *)modalViewController;
- (void)globallyPresentQueuedModal:(UIViewController *)modalViewController completion:(ModalCompletionBlock)completion;


// Should be called on the presented controller (not the presenter)
- (void)dismissQueuedModal;
- (void)dismissQueuedModalWithCompletion:(ModalCompletionBlock)completion;

- (void)presentQueuedModal:(UIViewController *)modalViewController usingAnimation:(QueuedModalAnimationType)animation completion:(ModalCompletionBlock)completion;
- (void)presentQueuedModal:(UIViewController *)modalViewController usingAnimation:(QueuedModalAnimationType)animation initialRect:(CGRect)initialRect completion:(ModalCompletionBlock)completion;
- (void)presentQueuedModal:(UIViewController *)modalViewController usingAnimation:(QueuedModalAnimationType)animation initialRect:(CGRect)initialRect priority:(QueuedModalPresentationPriority)priority completion:(ModalCompletionBlock)completion;
- (void)presentQueuedModal:(UIViewController *)modalViewController usingAnimation:(QueuedModalAnimationType)animation initialRect:(CGRect)initialRect endRect:(CGRect)endRect priority:(QueuedModalPresentationPriority)priority completion:(ModalCompletionBlock)completion;
- (void)presentQueuedModal:(UIViewController *)modalViewController usingAnimation:(QueuedModalAnimationType)animation initialRect:(CGRect)initialRect endRect:(CGRect)endRect priority:(QueuedModalPresentationPriority)priority overlayType:(QueuedModalOverlayType)overlayType completion:(ModalCompletionBlock)completion;

- (void)dismissQueuedModalUsingAnimation:(QueuedModalAnimationType)animation endRect:(CGRect)endRect completion:(ModalCompletionBlock)completion;

- (UIViewController *)queuedModalPresentationContext;
- (UIViewController *)globalQueuedModalPresentationContext;

@property (nonatomic, readonly) BOOL isPresentedAsQueuedModal;
@property (nonatomic, readonly) BOOL isOrWillBePresentedAsQueuedModal;

@property (nonatomic, readonly) BOOL isDisplayingQueuedModals;


@property(nonatomic,assign) BOOL definesQueuedModalPresentationContext;


- (void)dismissPresentedControllerOrQueuedModal;

- (void)dismissAllQueuedModalsOfPriority:(QueuedModalPresentationPriority)priority;
- (void)dismissAllQueuedModals;

- (void)dismissAllQueuedModalsOfClass:(Class)modalClass;
- (BOOL)isPresentingQueuedModalOfClass:(Class)modalClass;

@end


@interface UIViewController (QueuedModalBehaviors)

- (QueuedModalAnimationType)dismissModalAnimationType;
- (QueuedModalAnimationType)presentModalAnimationType;

- (BOOL)shouldDismissModalIfClickedOutside;
- (BOOL)modalWillDismissByClickingOutside; // return NO if you want to ignore.
- (UIColor *)dimmedBackgroundColor; // return nil to disable;
- (BOOL)adjustModalAsIfKeyboardIsVisible;

- (CGFloat)modalStartAndEndAlpha;
- (NSTimeInterval)modalAnimationDuration;
- (UIEdgeInsets)modalDimBackgroundEdgeInsets;

- (NSString *)queuedModalGroupIdentifier;

- (void)queuedModalDidBecomeChildOfWindow;

- (UIView *)queuedModalViewToScale;
- (BOOL)modalIsKeyboardResponsive;

@end


@interface QueuedModalSegue : UIStoryboardSegue

@property (nonatomic, assign) CGRect initialRect;
@property (nonatomic, assign) CGRect endRect;
@property (nonatomic, assign) QueuedModalOverlayType overlayType;
@property (nonatomic, assign) QueuedModalAnimationType animationType;

@end

// Will be presented on the root view controller
@interface RootQueuedModalSegue : QueuedModalSegue

@end

@interface GlobalQueuedModalSegue : QueuedModalSegue

@end

@interface UIStoryboardSegue (Dismiss)

- (void)dismissAnimated:(BOOL)animated;
- (void)dismissAnimated:(BOOL)animated completion:(void(^)(void))completion;

@end


