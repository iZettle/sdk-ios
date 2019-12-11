//
//  ManualCardInfo.h
//  iZettle
//
//  Created by Måns Bernhardt on 2011-10-17.
//  Copyright (c) 2011 Bit of Mind AB. All rights reserved.
//

@import Foundation;

typedef BOOL (^ValidCardPartBlock)(NSString *text);

@class CardIssuer;

@interface IZCardInfo : NSObject<NSCopying, NSMutableCopying>

- (id)initWithNumber:(NSString *)number year:(NSString *)year month:(NSString *)month hasChip:(BOOL)hasChip requiresPin:(BOOL)requiresPin;
+ (id)manualCardInfoWithNumber:(NSString *)number year:(NSString *)year month:(NSString *)month hasChip:(BOOL)hasChip requiresPin:(BOOL)requiresPin;
+ (id)manualCardInfo;

@property(nonatomic, copy, readonly) NSString *number;
@property(nonatomic, copy, readonly) NSString *year;
@property(nonatomic, copy, readonly) NSString *month;
@property(nonatomic, copy, readonly) NSString *code;

@property(nonatomic, readonly) BOOL hasChip;
@property(nonatomic, readonly) BOOL requiresPin;

@property(nonatomic, readonly) BOOL isValid;
@property(nonatomic, readonly) CardIssuer *issuer;

@property(nonatomic, copy, readonly) NSString *obfuscatedNumber;
@property(nonatomic, copy, readonly) NSString *lastDigits;

@end

extern NSString *const CardInfoIssuerDidChangeNotification;

@interface IZMutableCardInfo : IZCardInfo

@property(nonatomic, copy, readwrite) NSString *number;
@property(nonatomic, copy, readwrite) NSString *year;
@property(nonatomic, copy, readwrite) NSString *month;
@property(nonatomic, copy, readwrite) NSString *code;

@end

@interface IZCardInfo (Utilities) 

@property(nonatomic, readonly) ValidCardPartBlock validNumberBlock;
@property(nonatomic, readonly) ValidCardPartBlock validYearBlock;
@property(nonatomic, readonly) ValidCardPartBlock validMonthBlock;
@property(nonatomic, readonly) ValidCardPartBlock validCodeBlock;

@end
