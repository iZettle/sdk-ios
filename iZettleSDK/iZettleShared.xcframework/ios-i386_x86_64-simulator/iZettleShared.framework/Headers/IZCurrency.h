//
//  Currency.h
//  iZettle
//
//  Created by Måns Bernhardt on 2012-04-05.
//  Copyright (c) 2012 iZettle. All rights reserved.
//

@import Foundation;

// Formatter that will remove the non breaking space (unicode 00A0)
@interface NoSpaceNumberFormatter : NSNumberFormatter

@end

@interface IZCurrency : NSObject

+ (instancetype)currencyWithCode:(NSString *)code;

@property (nonatomic, readonly) NSString *code;
@property (nonatomic, readonly) NSNumberFormatter *formatter;

+ (void)setCurrentLocale:(NSLocale *)locale;

@end
