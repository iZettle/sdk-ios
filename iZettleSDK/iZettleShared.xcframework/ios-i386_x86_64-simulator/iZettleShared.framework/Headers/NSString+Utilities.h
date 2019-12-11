//
//  NSString+Utilities.h
//  iZettle
//
//  Created by Måns Bernhardt on 2011-06-30.
//  Copyright 2011 Babel Studios. All rights reserved.
//

@import Foundation;


@interface NSString (Utilities)

- (BOOL)matchesRegex:(NSString *)pattern;
- (BOOL)matchesRegex:(NSString *)pattern options:(NSRegularExpressionOptions)options;
- (NSArray<NSString *> *)matchesInRegex:(NSString *)pattern options:(NSRegularExpressionOptions)options;
- (BOOL)isNumeric;
- (BOOL)isValidEmailAddress;
- (BOOL)isValidPhoneNumber;
- (BOOL)isValidLuhn;
- (BOOL)contains:(NSString *)string;
- (BOOL)iz_versionGreaterThanVersion:(NSString *)version NS_SWIFT_NAME(versionGreaterThan(version:));
+ (NSString *)GUIDString;

@property (nonatomic, readonly) NSString *monogramString;

- (NSString *)izMd5String;
- (NSString *)izSha1String;

- (BOOL(^)(id value))validatationBlockFromRegex;

- (NSString *)stringByAppendingURLParams:(NSDictionary *)params;
- (NSDictionary *)parseURLParams;

- (NSData *)izDataFromHex;

@end

@interface NSString (HTMLExtensions)

+ (NSDictionary *)htmlEscapes;
+ (NSDictionary *)htmlUnescapes;
- (NSString *)htmlEscapedString;
- (NSString *)htmlUnescapedString;

@end
