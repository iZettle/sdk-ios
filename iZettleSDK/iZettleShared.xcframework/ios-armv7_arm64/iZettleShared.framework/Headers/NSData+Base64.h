//
//  NSData+Base64.h
//  iZettle
//
//  Created by Alexander Nordfelth on 2010-08-11.
//  Copyright (c) 2010 iZettle. All rights reserved.
//

@import Foundation;

@interface NSData (Base64)

+ (instancetype)izDataWithBase64EncodedString:(NSString *)string;     //  Padding '=' characters are optional. Whitespace is ignored.
- (NSString *)izBase64Encoding;

- (NSString *)izHexEncodeed;

@end
