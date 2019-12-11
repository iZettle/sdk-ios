//
//  NSDateFormatter+Utilities.h
//  iZettle
//
//  Created by Måns Bernhardt on 2012-03-28.
//  Copyright (c) 2012 iZettle. All rights reserved.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN 

@interface NSDateFormatter (Utilities)

+ (NSDateFormatter *)izDateFormatterUsingISO8601;

- (BOOL)isRelativeStringFromDatePossible:(NSDate *)date;
- (NSString *)relativeStringFromDateIfPossible:(NSDate *)date;

@end

NS_ASSUME_NONNULL_END
