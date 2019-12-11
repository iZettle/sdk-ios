//
//  IZFuture.h
//  iZettle
//
//  Created by Måns Bernhardt on 2014-10-28.
//  Copyright (c) 2014 iZettle. All rights reserved.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

// Tasks and Futures are used to handle asynchronous operations.
// You create a task and returns it's future. When the task is done you complete it and the future will be notified.
// Futures can be chained using then methods or run in parallel using all or any variants.
// Futures handles propagating of errors if a task i aborted and canceling of task that should be abandonned.


typedef NSError IZTaskError;

@protocol IZFutureScheduler
- (void)scheduleBlock:(dispatch_block_t)block;
@end



// A future is what should be returned by asynchronous methods. Set the onComplete block to receive the result or use the future togehter with other futures to build new futures.
@interface IZFuture<ResultType> : NSObject

// Cancel a future (and its potential children).
- (void)cancel;

@end

// A task is the actual asynchronous work. Create a task instance and return it's future. When the task is done call complete: with the result or abort: if it failed.

@interface IZTask<ResultType> : NSObject

+ (instancetype)task;

// onCancel will be called if an ongoing task is cancelled. Use it for clean up.
- (void)addCancelBlock:(void (^)(void))block;

// if error != nil the task will abort. If queue != nil the completion will be delivered asynchronously on queue
- (void)complete:(nullable ResultType)value orAbort:(nullable IZTaskError *)error onScheduler:(nullable id<IZFutureScheduler>)scheduler;

// Return the tasks future.
@property (nonatomic, readonly) IZFuture<ResultType> *future;

@property (nonatomic, readonly) BOOL hasBeenCancelled;
@property (nonatomic, readonly) BOOL hasResultOrError;
@property (nonatomic, readonly) BOOL hasCompletion; // FIXME: temp exposure... need a better solution...

@end



@interface IZFuture<ResultType> (Operations)

- (IZFuture *)thenComplete:(IZFuture *(^)(ResultType __nullable value, IZTaskError * __nullable error))block;

/// If the future completes the function is called with its result and the continues with the returned future.
@property (nonatomic, readonly) IZFuture *(^then)(IZFuture *(^)(ResultType __nullable value));

/// If the future is aborted the function is called with the error and then continues with the returned future.
#if !defined(__cplusplus)
@property (nonatomic, readonly) IZFuture *(^catch)(IZFuture *(^)(IZTaskError *error));
#else
- (IZFuture *(^)(IZFuture *(^)(IZTaskError *error)))catch;
#endif

/// If the future completes or aborts the function is called its result or error and then continues with the returned future.
@property (nonatomic, readonly) IZFuture * (^thenOrCatch)(IZFuture * _Nullable(^)(ResultType __nullable value, IZTaskError * __nullable error));

/// The function will be called if the future is completed, aborted or cancelled.
- (IZFuture *)always:(void (^)(void))block;
@property (nonatomic, readonly) IZFuture *(^finally)(void (^)(void));

/// The function will be called if the future is cancelled.
@property (nonatomic, readonly) IZFuture *(^onCancel)(void (^)(void));


/// When all futures has completed returns their result in an array
+ (IZFuture<NSArray *> *)all:(NSArray<IZFuture *> *)futures;

/// When any of the futures complete return it's result and cancel the others.
+ (IZFuture *)any:(NSArray<IZFuture *> *)futures;


@end


NS_ASSUME_NONNULL_END





