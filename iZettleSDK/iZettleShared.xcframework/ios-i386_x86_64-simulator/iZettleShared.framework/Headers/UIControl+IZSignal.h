//
//  UIControl+IZSignal.h
//  iZettleShared
//
//  Created by Said Sikira on 2018-12-16.
//  Copyright © 2018 iZettle. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "IZDisposable.h"

@class IZSignal<T>;

NS_ASSUME_NONNULL_BEGIN

/**
 Helper class to setup target actions
 */
@interface IZTargetAction : NSObject

/**
 Add a callback that will be executed once reciever sends an event
 */
- (id <IZDisposable>)addCallback:(void (^)(id))callback;
@end

@interface UIControl (IZSignal)

/**
 @return Signal that emits a value for a given control event once
 it's dispatched from a UIControl
 */
- (IZSignal *)iz_signalForControlEvents:(UIControlEvents)events;

/**
 @return Signal that emits a value for `UIControlEventsValueChanged`
 control event
 */
@property (nonatomic, readonly) IZSignal *izSignal;
@end

@interface UIButton (IZSignal)
@property (nonatomic, readonly) IZSignal *izSignal;
@end

@interface UISwitch (IZSignal)
@property (nonatomic, readonly) IZSignal *izSignal;
@end

@interface UIBarButtonItem (IZSignal)
@property (nonatomic, readonly) IZSignal *izSignal;
@end

NS_ASSUME_NONNULL_END
