//
//  NSDictionary+Utilities.h
//  iZettle
//
//  Created by Måns Bernhardt on 2011-09-21.
//  Copyright 2011 Bit of Mind AB. All rights reserved.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

@interface NSDictionary (Utilities) 

- (id _Nullable)nonNullObjectForKey:(id)aKey;

- (nullable id)objectWithKindOfClass:(Class)klass forKey:(id)aKey;
- (NSDecimalNumber *)decimalNumberForKey:(id)aKey;
- (NSDictionary *)dictionaryForKey:(id)aKey;

@end

@interface NSMutableDictionary (Utilities) 

- (void)setObjectOrNull:(id _Nullable)value forKey:(id)aKey;
- (void)setObjectIfNotNull:(id _Nullable)value forKey:(id)aKey;

@end

NS_ASSUME_NONNULL_END
