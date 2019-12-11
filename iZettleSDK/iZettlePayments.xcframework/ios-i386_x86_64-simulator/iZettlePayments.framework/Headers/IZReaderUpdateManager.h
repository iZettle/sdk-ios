//
//  IZReaderUpdateManager.h
//  iZettlePayments
//
//  Created by Andrei Valkovskii on 2018-10-31.
//  Copyright © 2018 iZettle. All rights reserved.
//

#import <Foundation/Foundation.h>

@class DatecsReader;
@class IZAccount;
@class IZFuture;
@class IZReaderUpdateState;

NS_ASSUME_NONNULL_BEGIN

@protocol IZReaderUpdateManagerDelegate <NSObject>

- (void)updateProgress:(IZReaderUpdateState *)state;

@end

@interface IZReaderUpdateManager : NSObject

@property (nonatomic, weak) id<IZReaderUpdateManagerDelegate> delegate;

- (instancetype)initWithReader:(DatecsReader *)reader account:(IZAccount *)account completion:(void(^)(NSError * _Nullable error))completion;

- (void)start;
- (void)complete;
- (void)cancel;

@end

NS_ASSUME_NONNULL_END
