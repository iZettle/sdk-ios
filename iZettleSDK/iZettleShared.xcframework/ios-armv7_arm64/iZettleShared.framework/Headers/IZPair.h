//
//  IZPair.h
//  iZettleShared
//
//  Created by Said Sikira on 2018-04-24.
//  Copyright © 2018 iZettle. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Defines a pair of values
 */
@interface IZPair<__covariant Left, __covariant Right> : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)pairWithLeft:(Left)left right:(Right)right;

@property (nonatomic, strong, readonly) Left left;
@property (nonatomic, strong, readonly) Right right;

@end

NS_ASSUME_NONNULL_END
