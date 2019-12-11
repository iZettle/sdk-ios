//
//  iZettleTranslationsDataSource.h
//  iZettle
//
//  Created by Mattias Jähnke on 2012-10-02.
//  Copyright (c) 2012 iZettle. All rights reserved.
//

@import Foundation;
@import iZettleShared;

NS_ASSUME_NONNULL_BEGIN

extern NSString *const iZettleTranslationsDataSourceShowKeysKey;
extern NSString *const KeysLanguageCode;

@interface IZettleTranslationsDataSource : NSObject<LocalizationDataSource>

@property (nonatomic, readonly) NSArray *availableLanguageIdentifiers;

- (id)initWithPreferredBundle:(NSBundle *) preferredBundle;

- (void)setOverrideLanguageIdentifier:(NSString * __nullable)languageIdentifier regionLocale:(NSLocale * __nullable)regionLocale;
- (NSString * __nullable)existingLanguageIdentifierForLanguageIdentifier:(NSString *)languageIdentifier;

- (NSDictionary *)translationDictionaryForLanguageIdentifier:(NSString *)languageIdentifier;
- (NSDictionary *)translationDictionary;

@end

NS_ASSUME_NONNULL_END
