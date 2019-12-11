//
//  NSURL+Utilities.h
//  iZettle
//
//  Created by Jens Utbult on 2012-03-14.
//  Copyright (c) 2012 iZettle. All rights reserved.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

@interface NSURL (Utilities)

- (NSDictionary *)izDictionaryFromQueryComponents;
- (NSURL *)izURLByAppendingQueryString:(NSString *)queryString;

- (NSURL *)izURLByAppendingPathFormat:(NSString *)format, ...;

- (NSURL *)izURLByAppendingURLParams:(NSDictionary *)params;

- (NSString *)izObfuscatedAbsoluteString NS_SWIFT_NAME(obfuscatedAbsoluteString());

@end

@interface NSURLComponents (Utilities)

- (void)izObfuscate;

@end

NS_ASSUME_NONNULL_END

