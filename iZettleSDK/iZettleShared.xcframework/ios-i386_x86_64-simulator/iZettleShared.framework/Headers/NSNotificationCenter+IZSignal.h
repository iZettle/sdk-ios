//
//  NSNotificationCenter+IZSignal.h
//  iZettleShared
//
//  Created by Said Sikira on 2018-07-21.
//  Copyright © 2018 iZettle. All rights reserved.
//

@import Foundation;
@class IZSignal<Value>;

NS_ASSUME_NONNULL_BEGIN

@interface NSNotificationCenter (IZSignal)
/// Returns a signal for notifications named `name` and given object
- (IZSignal<NSNotification *> *)iz_signalForNotificationWithName:(NSNotificationName)name object:(nullable id)object;

/// Returns a signal for notifications named `name`.
- (IZSignal<NSNotification *> *)iz_signalForNotificationWithName:(NSNotificationName)name;
@end

NS_ASSUME_NONNULL_END
