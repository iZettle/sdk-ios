//
//  LocalizationManager.h
//  iZettle
//
//  Created by Måns Bernhardt on 2012-02-22.
//  Refactored by Mattias Jähnke on 2012-10-02
//  Copyright (c) 2012 iZettle. All rights reserved.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

extern NSString *const LocalizationChangedNotification;

@protocol LocalizationDataSource <NSObject>
- (NSString * __nullable)stringForKey:(NSString *)key withLanguageIdentifier:(NSString *)languageIdentifier fallbackToEnglish:(BOOL)fallbackToEnglish;

- (NSString *)currentLanguageIdentifier;
- (NSLocale *)currentRegionLocale;
@end

@protocol Localizable<NSObject>
- (void)setNeedsLocalization;
@end

@interface LocalizationManager : NSObject

+ (LocalizationManager *)shared;

@property (nonatomic, weak) NSObject<LocalizationDataSource>* dataSource;
@property (nonatomic, readonly) NSString *languageIdentifier;
@property (nonatomic, readonly) NSLocale *regionLocale;

- (NSString * __nullable)localizedStringForKey:(NSString *)key;
- (NSString * __nullable)localizedStringForKey:(NSString *)key fallback:(BOOL)fallback;
- (NSString * __nullable)localizedStringForKey:(NSString *)key withLanguageIdentifier:(NSString *)languageIdentifier;
- (NSString * __nullable)localizedStringForKey:(NSString *)key withLanguageIdentifier:(NSString *)languageIdentifier fallback:(BOOL)fallback;

- (void)registerLocalizable:(id<Localizable>)localizable;
- (void)unregisterLocalizable:(id<Localizable>)localizable;

- (void)setDateFormatter:(NSDateFormatter *)formatter forKey:(NSString *)key;
- (NSDateFormatter * __nullable)dateFormatterForKey:(NSString *)key;

- (void)setNumberFormatter:(NSNumberFormatter *)formatter forKey:(NSString *)key;
- (NSNumberFormatter * __nullable)numberFormatterForKey:(NSString *)key;

- (void)refreshAllControllersAndViews;

- (BOOL)hasLocalizedStringForKey:(NSString *)key;

@end

NS_ASSUME_NONNULL_END