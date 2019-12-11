//
//  IZCallbacker.h
//  iZettleShared
//
//  Created by Said Sikira on 2018-04-23.
//  Copyright © 2018 iZettle. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IZDisposable.h"

NS_ASSUME_NONNULL_BEGIN

@interface IZCallbacker<Value> : NSObject
typedef void (^IZCallback)(Value);
+ (instancetype)callbacker;

- (id <IZDisposable>)add:(IZCallback)callback;
- (void)callAllWithValue:(Value)value NS_SWIFT_NAME(callAll(with:));

@property (nonatomic, readonly) BOOL isEmpty;
@end

NS_ASSUME_NONNULL_END
