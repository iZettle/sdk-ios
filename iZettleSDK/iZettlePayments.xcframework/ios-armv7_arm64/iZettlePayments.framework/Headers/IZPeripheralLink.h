//
//  DeviceLink.h
//  iZettlePayments
//
//  Created by Mattias Jähnke on 2017-08-17.
//  Copyright © 2017 iZettle. All rights reserved.
//

@import Foundation;
@import iZettleShared;

@protocol IZPeripheralLink;

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(PeripheralLinkDelegate)
@protocol IZPeripheralLinkDelegate <NSObject>

- (void)linkDidConnect:(id<IZPeripheralLink>)link;
- (void)link:(id<IZPeripheralLink>)link didDisconnectWithError:(NSError * _Nullable)error;
- (void)link:(id<IZPeripheralLink>)link didFailToConnectWithError:(NSError *)error;

- (void)link:(id<IZPeripheralLink>)link receivedData:(NSData *)data;
- (void)link:(id<IZPeripheralLink>)link dataReceiveFailedWithError:(NSError *)error;

@end


NS_SWIFT_NAME(PeripheralLink)
@protocol IZPeripheralLink <NSObject>

@property (nonatomic, weak) id<IZPeripheralLinkDelegate> delegate;
@property (nonatomic, strong, readonly) NSString *name;

- (void)open;
- (void)close;

- (IZFuture *)writeData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
