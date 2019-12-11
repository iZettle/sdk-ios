//
//  UIView+Utilities.h
//  iZettle
//
//  Created by Måns Bernhardt on 2011-06-30.
//  Copyright 2011 Babel Studios. All rights reserved.
//

@import UIKit;


@interface UIView (Utilities)

/// Returns a new view that does not convert the autoresizing mask into constraints.
+ (instancetype)newIzAutoLayoutView;

/// Initializes and returns a new view that does not convert the autoresizing mask into constraints.
- (instancetype)initIzForAutoLayout;

- (UIImageView *)izImageViewWithSnapshot;

// toView added to fromView.superview, fromView removed from its superview
+ (void)izBasicCubeTransitionFromView:(UIView *)fromView toView:(UIView *)toView duration:(NSTimeInterval)duration reverse:(BOOL)reverse completion:(void (^)(BOOL finished))completion;

+ (void)izAnimateWithKeyboardUserInfo:(NSDictionary *)userInfo additionalOptions:(UIViewAnimationOptions)options animations:(dispatch_block_t)animations;

+ (void)izAnimateWithUserInteractionAndDuration:(NSTimeInterval)duration animations:(dispatch_block_t)animations;
+ (void)izAnimateWithUserInteractionAndDuration:(NSTimeInterval)duration animations:(dispatch_block_t)animations completion:(void (^)(BOOL finished))completion;

- (UIView *)izFindFirstResponder;
- (UIResponder *)izFindFirstPossibleResponder;
- (NSArray *)izFindPossibleResponders;

@property(nonatomic, readonly) UIView *izRootView; // not window;

+ (void)izPushDisableAnimations;
+ (void)izPopDisableAnimations;

+ (void)izPerformWithoutAnimation:(dispatch_block_t)block;

- (void)izAddConstraintToSubview:(UIView *)subview;
- (void)izAddConstraintToSubview:(UIView *)subview withEdgeInsets:(UIEdgeInsets)edgeInsets;

- (NSLayoutConstraint *)izAddConstraintWithFixedWidth:(CGFloat)width;
- (NSLayoutConstraint *)izAddConstraintWithFixedHeight:(CGFloat)height;
- (void)izAddConstraintCenterVerticallyToSubview:(UIView *)subview offset:(CGFloat)offset fixedHeight:(CGFloat)height;

- (void)izAddConstraintToSubview:(UIView *)subview visualConstraints:(NSArray *)visualConstraints metrics:(NSDictionary *)metrics;

- (void)izRemoveAllConstraintsOnSelfAndSubviews;

@property(nonatomic, readonly) UIViewController *izViewController;


- (void)izEnumerateSubviews:(void(^)(UIView *view, BOOL *stop))block;
- (void)izEnumerateSubviewsThatIsKindOfClass:(Class)klass block:(void(^)(id view, BOOL *stop))block;


- (id)izFindClosestAncesterOfClass:(Class)klass;
- (id)izFindFirstSubviewThatIsKindOfClass:(Class)klass;


@end



