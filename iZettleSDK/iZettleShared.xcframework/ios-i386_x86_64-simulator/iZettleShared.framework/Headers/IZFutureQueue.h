//
//  IZFutureQueue.h
//  iZettleShared
//
//  Created by Måns Bernhardt on 2015-05-29.
//  Copyright (c) 2015 iZettle. All rights reserved.
//

@import Foundation;

#import "IZFuture+Utilities.h"

NS_ASSUME_NONNULL_BEGIN

@interface IZFutureQueue : NSObject

- (instancetype)initWithResource:(nullable id)resource dispatchOnQueue:(nullable dispatch_queue_t)dispatchQueue completeOnQueue:(nullable dispatch_queue_t)completionQueue;

+ (instancetype)queueWithResource:(nullable id)resource;

// If a non nil dispatchQueue is provided, execute will be called on that queue
// If a non nil completionQueue is provided, the return execute future will be called on that queue
+ (instancetype)queueWithResource:(nullable id)resource dispatchOnQueue:(nullable dispatch_queue_t)dispatchQueue completeOnQueue:(nullable dispatch_queue_t)completionQueue;

@property (nonatomic, readonly) BOOL isEmpty;
@property (nonatomic, weak, readonly) id resource;
@property (nonatomic, readonly) NSError *closedError; // non nil if queue has been closed

// Make sure to not call another operation on the same queue as it will deadlock, instead use executeBatch
- (IZFuture *)executeFunction:(IZFutureFunction)function;
@property (nonatomic, readonly) IZFuture *(^execute)(IZFuture *(^)(void));
@property (nonatomic, readonly) IZFuture *(^executeBatch)(IZFuture *(^)(id queue));

// The returned future will complete when the queue becomes empty.
- (IZFuture *)whenQueueBecomesEmpty;

- (void)abortQueuedExecutionWithError:(NSError *)error;
- (void)closeAndAbortQueuedExecutionWithError:(NSError *)error;

@end

@interface IZFutureQueue (Utilities)

// The returned future will complete if the queue is empty or becomes empty.
- (IZFuture *)ifOrWhenQueueBecomesEmpty;

// The returned future will complete when queue has been empty for timeout seconds
- (IZFuture *)afterQueueHasBeenEmptyForTimeout:(NSTimeInterval)timeout;

@end

NS_ASSUME_NONNULL_END

