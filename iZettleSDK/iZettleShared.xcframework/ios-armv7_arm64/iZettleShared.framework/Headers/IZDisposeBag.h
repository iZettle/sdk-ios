//
//  IZDisposeBag.h
//  iZettleShared
//
//  Created by Said Sikira on 2018-04-22.
//  Copyright © 2018 iZettle. All rights reserved.
//

@import Foundation;
@class IZFuture;
#import "IZDisposable.h"

NS_ASSUME_NONNULL_BEGIN

@interface IZDisposeBag : NSObject <IZDisposable>
+ (instancetype)bag;
+ (instancetype)bagWithDisposables:(NSArray<id <IZDisposable>> *)disposables;

- (void)addDisposable:(id <IZDisposable>)disposable;
- (void)addFuture:(IZFuture *)future;
- (void)addObject:(id)object;

@end

NS_ASSUME_NONNULL_END
