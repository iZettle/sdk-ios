//
//  NavigationBar.h
//  iZettleShared
//
//  Created by Mattias Jähnke on 2013-05-07.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import UIKit;

#define NAVIGATIONBAR_BUTTON_SIZE ([UIDevice isCurrentlyRegularSized] ? 50 : 44)
#define NAVIGATIONBAR_RIGHT_PADDING ([UIDevice isCurrentlyRegularSized] ? 20 : 14)
#define NAVIGATIONBAR_LEFT_PADDING ([UIDevice isCurrentlyRegularSized] ? 20 : 7)
#define NAVIGATIONBAR_MODAL_RIGHT_PADDING ([UIDevice isCurrentlyRegularSized] ? 12 : 14)
#define NAVIGATIONBAR_MODAL_LEFT_PADDING ([UIDevice isCurrentlyRegularSized] ? 20 : 14)

typedef NS_ENUM(NSUInteger, NavigationBarTitleAlignment) {
    NavigationBarTitleAlignmentCenter,
    NavigationBarTitleAlignmentRight,
    NavigationBarTitleAlignmentLeft,
};

@interface IZNavigationBar : UINavigationBar

- (void)_sharedInit;

@property (nonatomic, assign) CGFloat rightPadding;
@property (nonatomic, assign) CGFloat leftPadding;

@property (nonatomic, readonly) UIColor *navBackgroundColor;
@property (nonatomic, readonly) UIColor *barItemHighlightedColor;
@property (nonatomic, readonly) UIColor *barItemColor;
@property (nonatomic, readonly) UIColor *barItemDisabledColor;
@property (nonatomic, readonly) UIColor *lineColor;

- (void)styleNavigationBarTitleAndStepperWithItem:(UINavigationItem *)item;

@property (nonatomic, assign) CGFloat height;

@end


@interface BacklayerNavigationBar : IZNavigationBar
@end


// This is white, so should only be used for "Real" modals (iPad and SOME iPhone modals (global))
@interface ModallayerNavigationBar : IZNavigationBar
@end


@interface UINavigationItem (NavigationBar)

@property (nonatomic, assign) NavigationBarTitleAlignment navigationBarTitleAlignment;
@property (nonatomic, assign) CGFloat navigationBarLeftPadding;
@property (nonatomic, assign) CGFloat navigationBarRightPadding;

// This property is to be used on modals on iPhone to correct the layout of the titleView
@property (nonatomic, assign) BOOL iphoneUseSuperViewWidth;

@end
