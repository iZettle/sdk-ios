//
//  IZKeyboard.h
//  iZettleShared
//
//  Created by Mattias Jähnke on 2014-11-25.
//  Copyright (c) 2014 iZettle. All rights reserved.
//

@import UIKit;

typedef void(^ViewportBlock)(CGRect viewport);

@interface UIView (Viewport)

// returns the views current viewport in views coordinate space and clipped to its bounds
@property (nonatomic, readonly) CGRect izViewport;

- (id)izAddViewportObserverBlock:(ViewportBlock)block;
- (id)izAddAnimatedViewportObserverBlock:(ViewportBlock)block;

- (void)izRemoveViewportObserver:(id)observer;
- (void)izRemoveViewportObservers;

@end