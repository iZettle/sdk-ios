//
//  LocalizationExtensions.h
//  iZettle
//
//  Created by Mattias Jähnke on 2012-10-02.
//  Copyright (c) 2012 iZettle. All rights reserved.
//

@import UIKit;

NS_ASSUME_NONNULL_BEGIN

@interface NSObject (Localizable)

- (NSString *)localizedStringForKey:(NSString *)key componentID:(int16_t)componentID;

@end


@interface NSString (Localizable)

@property (nonatomic, readonly) NSString *izLocalizedString;
- (NSString *)localizedStringWithLanguageIdentifier:(NSString *)languageIdentifier;

@property (nonatomic, readonly) NSString *localizedStringWithoutFallback;
- (NSString *)localizedStringWithoutFallbackWithLanguageIdentifier:(NSString *)languageIdentifier;

@property (nonatomic, readonly) NSString *localizeKeyString; // Add # has prefix
@property (nonatomic, readonly) BOOL isLocalizeKey; // Has # prefix

@property (nonatomic, readonly) NSString *accessibilityIdentifierFromTranslationKey;

@end


@interface UIView (Localizable)

- (void)localizeView;
- (void)localizeViewAndSubviews;

@end

@interface NSNumberFormatter (Localizable)

+ (NSNumberFormatter *)percentageFormatterWithNoDecimals;
+ (NSNumberFormatter *)percentageFormatterWithOptionalDecimals;
+ (NSNumberFormatter *)integerFormatter;

@end


@interface NSNumber (Localizable)

@property (nonatomic, readonly) NSString *percentageStringWithNoDecimals;
@property (nonatomic, readonly) NSString *percentageStringWithOptionalDecimals;
@property (nonatomic, readonly) NSString *integerString;

@end

extern NSString *stringFromInteger(NSInteger value);

NS_ASSUME_NONNULL_END
