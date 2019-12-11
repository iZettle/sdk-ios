//
//  HerdAttempt.h
//  HerdSample
//
//  Created by Mattias Jähnke on 2014-03-10.
//  Copyright (c) 2014 iZettle. All rights reserved.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, AttemptState) {
    AttemptStateRunning,
    AttemptStateSuccess,
    AttemptStateFailed,
    AttemptStateTimedOut,
};

@interface Attempt : NSObject

// **** INITIALIZERS ****

/*!
 Initialize a new attempt with a given type
 */
+ (instancetype)attemptWithType:(NSString *)type;

// **** PROPERTIES ****

/*!
 Set the number of seconds to wait until the attempt is timed out. When an attempt is timed out, it is removed from the persistance store and will not report.
 Set the timeout to 0 to cancel a timeout.
 */
@property (nonatomic, assign) NSTimeInterval timeout;

/*!
 State of the Attempt
 */
@property (nonatomic, readonly) AttemptState state;

// Reportable data
/*!
 Any custom fields that is to be reported.
 */
@property (nullable, nonatomic, strong) NSDictionary *extra;

/*!
 The reason why the attempt was considered failed
 */
@property (nullable, nonatomic, copy) NSString *failureReason;

/*!
 Type of attempt. Can be used to group attempts
 */
@property (nonatomic, copy) NSString *type;

/*!
 NSDate representation of when the attempt started
 */
@property (nonatomic, readonly) NSDate *startDate;

/*!
 NSDate representation of when the attempt ended (nil if timed out)
 */
@property (nullable, nonatomic, readonly) NSDate *endDate;

// **** METHODS ****

/*!
 Consider the attempt failed with a reason (pass nil for empty)
 \param failureReason       Plain text string giving a description why the attempt failed
 */
- (void)considerAttemptFailedWithReason:(NSString * _Nullable)failureReason;
- (void)considerAttemptFailedWithError:(NSError *)error;

/*!
 Consider the attempt successful
 */
- (void)considerAttemptSuccessful;

@end

@interface Attempt (Utils)

- (void)considerSuccessfulOrFailedWithError:(NSError * _Nullable)error;

@end

NS_ASSUME_NONNULL_END
