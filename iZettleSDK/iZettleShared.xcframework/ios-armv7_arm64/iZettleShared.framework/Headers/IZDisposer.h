//
//  IZDisposer.h
//  iZettleShared
//
//  Created by Said Sikira on 2018-04-22.
//  Copyright © 2018 iZettle. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IZDisposable.h"

NS_ASSUME_NONNULL_BEGIN

@interface IZDisposer : NSObject <IZDisposable>
+ (instancetype)disposerWithBlock:(void(^)(void))block;
@end

NS_ASSUME_NONNULL_END
