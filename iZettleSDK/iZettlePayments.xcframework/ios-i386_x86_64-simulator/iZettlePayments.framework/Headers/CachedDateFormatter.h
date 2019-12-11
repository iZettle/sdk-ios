//
//  CachedDateFormatter.h
//  iZettleStorePurchase
//
//  Created by Mattias Jähnke on 2014-04-28.
//  Copyright (c) 2014 iZettle. All rights reserved.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

@interface CachedDateFormatter : NSDateFormatter

// Check cache, create a new formatter. formatter automatically change locale.
+ (instancetype)cachedDateFormatterWithDateStyle:(NSDateFormatterStyle)dateStyle timeStyle:(NSDateFormatterStyle)timeStyle timeZone:(nullable NSTimeZone *)timeZone;

+ (instancetype)cachedDateFormatterWithDateFormat:(NSString *)dateFormat timeZone:(nullable NSTimeZone *)timeZone;

@end

NS_ASSUME_NONNULL_END
