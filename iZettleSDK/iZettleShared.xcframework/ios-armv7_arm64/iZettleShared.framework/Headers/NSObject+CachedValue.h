//
//  NSObject+CachedValue.h
//  iZettleShared
//
//  Created by Mattias Jähnke on 2015-04-22.
//  Copyright (c) 2015 iZettle. All rights reserved.
//

@import Foundation;

@class IZFuture;

@interface NSObject (CachedValue)

- (IZFuture *)izCachedValueForKey:(NSString *)key createBlock:(IZFuture *(^)(void))createBlock;
- (IZFuture *)izCachedValueAndErrorForKey:(NSString *)key createBlock:(IZFuture *(^)(void))createBlock;
- (void)izClearCachedValueForKey:(NSString *)key;

@end
