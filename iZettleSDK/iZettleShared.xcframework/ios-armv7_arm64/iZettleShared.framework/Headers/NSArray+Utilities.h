//
//  NSArray+Utilities.h
//  iZettleShared
//
//  Created by Mattias Jähnke on 2015-05-28.
//  Copyright (c) 2015 iZettle. All rights reserved.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

@interface NSArray (Utilities)

+ (BOOL)iz_isNilOrEmpty:(NSArray * _Nullable)array NS_REFINED_FOR_SWIFT;
+ (BOOL)iz_isNotNilOrEmpty:(NSArray *)array;

- (nullable id)iz_objectPassingTest:(BOOL (^)(id))predicate NS_REFINED_FOR_SWIFT;
- (instancetype)iz_filter:(BOOL (^)(id))predicate NS_REFINED_FOR_SWIFT;

- (instancetype)izMap:(id(^)(id value))transformBlock;

@end

NS_ASSUME_NONNULL_END
