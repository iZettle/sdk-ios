//
//  AccessoryListener.h
//  iZettlePayments
//
//  Created by Andrei Valkovskii on 2018-05-08.
//  Copyright © 2018 iZettle. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class IZAccessoryService;

NS_SWIFT_NAME(AccessoryListenerDelegate)
@protocol IZAccessoryListenerDelegate <NSObject>

- (void)didConnectAccessoryService:(IZAccessoryService *)service NS_SWIFT_NAME(didConnect(_:));
- (void)didDisconnectAccessoryService:(IZAccessoryService *)service NS_SWIFT_NAME(didDisconnect(_:));

@end

NS_SWIFT_NAME(AccessoryListener)
@interface IZAccessoryListener : NSObject

@property (nonatomic, weak) id<IZAccessoryListenerDelegate> delegate;

+ (instancetype)accessoryListenerWithProtocols:(NSArray<NSString *> *)protocols;

- (void)activate;
- (void)deactivate;

@end

NS_ASSUME_NONNULL_END
