//
//  IZFuture+Utilities.h
//  FutureObjC
//
//  Created by Måns Bernhardt on 2014-10-28.
//  Copyright (c) 2014 Bit of Mind. All rights reserved.
//

@import Foundation;
@import UIKit;
#import "IZFuture.h"
#import "IZDisposable.h"

NS_ASSUME_NONNULL_BEGIN

typedef void (^IZFutureSchedulerBlock)(dispatch_block_t block);

@interface IZFutureScheduler : NSObject<IZFutureScheduler>

+ (instancetype)futureSchedulerWithBlock:(IZFutureSchedulerBlock)schedulerBlock;

@end

@interface IZFutureScheduler (Utilities)

+ (instancetype)futureSchedulerWithDispatchQueue:(dispatch_queue_t)queue;

@end


@interface IZTask<ResultType> (Utilities)

- (void)complete:(nullable ResultType)value orAbort:(nullable IZTaskError *)error onQueue:(nullable dispatch_queue_t)queue;
- (void)complete:(nullable ResultType)value onQueue:(dispatch_queue_t)queue;
- (void)complete:(nullable ResultType)value;

- (void)abort:(IZTaskError *)error onQueue:(dispatch_queue_t)queue;
- (void)abort:(IZTaskError *)error;

- (void)complete:(nullable ResultType)value orAbort:(nullable IZTaskError *)error;

@property (nonatomic, readonly) void (^onCancel)(void (^)(void));

@end

typedef IZFuture * _Nonnull (^IZFutureFunction)(void);


@interface IZFuture<ResultType> (Utilities)

// To listen in and handle future results, but dont affect the future.
@property (nonatomic, readonly) IZFuture *(^onResult)(void(^)(ResultType value));
@property (nonatomic, readonly) IZFuture *(^onError)(void(^)(IZTaskError *error));
@property (nonatomic, readonly) IZFuture *(^onResultOrError)(void(^)(ResultType __nullable value, IZTaskError * __nullable error));
@property (nonatomic, readonly) IZFuture *(^onErrorOrCancel)(void(^function)(IZTaskError * __nullable error));

// Temp fix to workaround current uncertainties with IZFuture's guarantees to callback on correct scheduler. 
@property (nonatomic, readonly) IZFuture *(^finallyOnMain)(void (^)(void));

+ (IZFuture<ResultType> *)futureWithResult:(nullable ResultType)result;
+ (IZFuture<ResultType> *)futureWithError:(IZTaskError *)error;

/// When the future complete function is called with its result and continues with what function returns.
@property (nonatomic, readonly) IZFuture *(^thenResult)(id __nullable (^)(ResultType __nullable value));


+ (IZFuture<ResultType> *)futureWithResult:(nullable ResultType)result orAbort:(nullable IZTaskError *)error;

// Change "shouldRepeat" to YES before functino complete to make function be called again after it completes (for both success or failure).
+ (IZFuture *)repeatFunction:(IZFuture *(^)(BOOL *shouldRepeat))function;
+ (IZFuture *)repeatForever:(IZFutureFunction)function;

+ (IZFuture *)repeatFunction:(IZFuture *(^)(ResultType value))function count:(int)count; // function is passed the index
+ (IZFuture *)repeatFunction:(IZFuture *(^)(void))function whilePredicate:(BOOL(^)(ResultType value))predicate; // predicat is passed the result from the function's predicate
+ (IZFuture *)repeatFunction:(IZFuture *(^)(void))repeatFunction ifFunctionIsCalled:(IZFutureFunction)resetFunction;
+ (IZFuture *)repeatForeverFunction:(IZFuture *(^)(void))repeatFunction;

+ (IZFuture *)mapValues:(NSArray *)values withBlock:(IZFuture *(^)(ResultType value))block;

+ (IZFuture *)waitForNotificationWithName:(NSString *)notificationName object:(nullable id)object predicate:(BOOL(^)(NSNotification *n))predicate;
+ (IZFuture *)waitForNotificationWithName:(NSString *)notificationName object:(nullable id)object;
+ (IZFuture *)notifyForNotificationWithName:(NSString *)notificationName object:(nullable id)object notifyBlock:(void(^)(NSNotification *n))notifyBlock;

+ (IZFuture *)sleep:(NSTimeInterval)time;
+ (IZFuture *)forever;
+ (IZFuture *)abortWithError:(NSError *)error afterTimeout:(NSTimeInterval)timeout;

+ (IZFuture *)performOnlyOneAtTheTimeForKey:(NSString *)key block:(IZFutureFunction)block;
+ (void)abortFuturesPerformedOnlyOneAtTheTimeUsingKey:(NSString *)key withError:(NSError *)error;

+ (IZFuture *)futureOnQueue:(dispatch_queue_t)queue;
+ (IZFuture *)onErrorRetryCount:(NSInteger)retryCount function:(IZFutureFunction)function errorPredicate:(nullable BOOL(^)(NSError * error))errorPredicate;

- (IZFuture *)continueOnQueue:(dispatch_queue_t)queue;
@property(readonly) IZFuture *continueOnMainQueue;

+ (IZFuture *)performInBackgroundAndContinueOnMainQueueUsingFunction:(IZFutureFunction)function;
- (IZFuture *)measureTime:(void(^)(NSTimeInterval time))block;

+ (IZFuture *)performAndRepeatOnNotificationNamed:(NSString *)notification object:(nullable id)object function:(dispatch_block_t)function;

- (IZFuture *)ignoreCancel;

/**
 Returns a `Disposable` the will cancel `self` when being disposed.

 @note The disposable will hold a weak reference to `self` to not delay the deallocation of `self`.
 */
- (id <IZDisposable>)disposable;

@end


@interface NSObject (Future)

- (void)izInstallFuture:(IZFuture *)future withName:(NSString *)name;
- (void)izInstallFuture:(IZFuture *)future;
- (void)izCancelInstalledFutureWithName:(NSString *)name;
- (void)cancelAllInstalledFutures;

@end


NS_ASSUME_NONNULL_END


