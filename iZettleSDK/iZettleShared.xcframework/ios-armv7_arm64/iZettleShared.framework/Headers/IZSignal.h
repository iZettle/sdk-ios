//
//  IZSignal.h
//  iZettleShared
//
//  Created by Said Sikira on 2018-04-22.
//  Copyright © 2018 iZettle. All rights reserved.
//

@import Foundation;

@class IZCallbacker<Type>;
@class IZFuture<Type>;
@class IZPair<Left, Right>;

#import "IZDisposable.h"

NS_ASSUME_NONNULL_BEGIN

/// An abstraction for observing values over time
@interface IZSignal<__covariant Value> : NSObject

#pragma mark Type definitions

typedef void (^IZCallback)(Value);
typedef id <IZDisposable> _Nonnull (^IZDisposableCallback)(IZCallback);

#pragma mark Initializers

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithCallback:(IZDisposableCallback)onEvent;
+ (instancetype)signalWithCallback:(IZDisposableCallback)onEvent;

/**
 Initialize a signal with a callbacker. Calling the callbacker with a value
 will push new signal event.
 */
- (instancetype)initWithCallbacker:(IZCallbacker<Value> *)callbacker;

#pragma mark Listeners

/// Start listening on values via the provided `callback`
/// Dispose returned disposable to stop listening
- (id <IZDisposable>)onValue:(IZCallback)callback
__attribute__((warn_unused_result)) NS_REFINED_FOR_SWIFT;

#pragma mark Transforms

/// Returns a new signal transforming values using `transform`
- (IZSignal *)map:(id(^)(id obj))transform NS_REFINED_FOR_SWIFT;

/// Returns a new signal transforming values using `transform` unless `transform` returns nil where the value will be discarded.
- (IZSignal *)compactMap:(_Nullable id(^)(id obj))transform NS_REFINED_FOR_SWIFT;

/// Returns a new signal where values evaluated false by `predicate` will be discarded.
- (IZSignal *)filter:(BOOL(^)(id obj))predicate NS_REFINED_FOR_SWIFT;

/// Returns a new signal emitting distinct contiguous values by evaluating `isSame`
- (IZSignal *)distinct:(BOOL(^)(id left, id right))isSame NS_REFINED_FOR_SWIFT;

#pragma mark Utilities

/**
 Returns a future that will succeed for when `self` signals its first value
 */
- (IZFuture<Value> *)future;

@end

/// Returns a new signal combining the latest values from the provided signals
IZSignal<IZPair *> * iz_combineLatest(IZSignal * first, IZSignal * second) NS_REFINED_FOR_SWIFT;

/**
 Returns a new signal merging the values emitted from provided signals
 */
IZSignal * iz_merge(IZSignal * lhs, IZSignal * rhs) NS_REFINED_FOR_SWIFT;

NS_ASSUME_NONNULL_END
