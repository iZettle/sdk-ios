//
//  NSDictionary+EncodedQueryString.h
//  iZettle
//
//  Created by Jens Utbult on 2011-08-25.
//  Copyright 2011 iZettle AB. All rights reserved.
//

@import Foundation;

@interface NSDictionary (EncodedQueryString)

- (NSString *)encodedQueryString;
+ (NSDictionary *)decodeQueryString:(NSString *)queryString;

@end
