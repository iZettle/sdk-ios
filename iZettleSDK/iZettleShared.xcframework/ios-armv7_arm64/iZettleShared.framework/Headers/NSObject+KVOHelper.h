//
//  NSObject+KVOHelper.h
//  iZettleShared
//
//  Created by Måns Bernhardt on 2013-05-14.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import Foundation;


typedef void(^KVOBlock)(id newValue);

@interface NSObject (KVOHelper)

- (void)startObserveKeyPath:(NSString *)keyPath action:(KVOBlock)action;

- (void)stopObserveKeyPath:(NSString *)keyPath action:(KVOBlock)action;
- (void)stopObserveKeyPath:(NSString *)keyPath;
- (void)stopObserve;


- (dispatch_block_t)observeNotificationOnce:(NSString *)notificationName object:(id)object usingBlock:(void (^)(NSNotification *note))block;

@end
