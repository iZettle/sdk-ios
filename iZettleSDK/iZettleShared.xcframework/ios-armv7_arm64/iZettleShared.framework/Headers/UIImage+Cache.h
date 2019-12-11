//
//  UIImage+Cache.h
//  iZettleShared
//
//  Created by Måns Bernhardt on 2013-08-12.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import UIKit;


typedef UIImage *(^ImageCreationBlock)(void);

/* Simple cache that will be cleared at low memory. If image is not in cache the creation block will be called to create it. The completion block might be called on a background queue. */

@interface UIImage (Cache)

+ (UIImage *)imageWithIdentifier:(NSString *)identifier;
+ (UIImage *)imageWithIdentifier:(NSString *)identifier creationBlock:(ImageCreationBlock)creationBlock;
+ (void)registerImageCreationBlock:(ImageCreationBlock)creationBlock forIdentifier:(NSString *)identifier;

+ (void)imageWithIdentifier:(NSString *)identifier completionBlock:(void (^)(UIImage *image))completionBlock;
+ (void)imageWithIdentifier:(NSString *)identifier creationBlock:(ImageCreationBlock)creationBlock completionBlock:(void (^)(UIImage *image))completionBlock;

+ (void)clearCache;
+ (void)clearCacheForIdentifier:(NSString *)identifier;

+ (void)clearCacheAndCreationBlocks;
+ (void)clearCacheAndCreationBlockForIdentifier:(NSString *)identifier;

// Debug
+ (NSDictionary *)_cache;

@end
