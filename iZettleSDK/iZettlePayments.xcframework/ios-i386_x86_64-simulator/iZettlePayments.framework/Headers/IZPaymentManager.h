// 
// Copyright © 2019 iZettle. All rights reserved.
// 

#import "IZNecessaryReaderUpdateProtocol.h"

@import iZettleShared;
@import Foundation;

@class IZCardReader;
@class IZPaymentConfiguration;
@class IZCardPaymentInfo;
@class IZReaderSelection;
@class IZNecessaryBackgroundReaderUpdate;

NS_ASSUME_NONNULL_BEGIN

@protocol IZPaymentManagerDelegate

- (void)presentReaderSelection:(IZReaderSelection *)readerSelection;

- (void)presentBluetoothIsOff;
- (void)presentBluetoothUnauthorized;
- (void)presentInternetIsOff;

- (void)presentEstablishConnection;
- (void)updateEstablishConnectionWithTitle:(id)title subtitle:(id)subtitle;

- (void)presentReaderUpdate:(id<IZNecessaryReaderUpdateProtocol>)readerUpdate;
- (IZFuture *)presentError:(NSError *)error showButton:(BOOL)showButton;
- (void)presentReconnection;

@end

@interface IZPaymentManager : NSObject

@property (nonatomic, copy, nullable) IZFuture<IZCardPaymentInfo *> *(^debugCharge)(IZPaymentConfiguration *configuration, IZCardReader *reader);

@property (nonatomic, weak) id<IZPaymentManagerDelegate>delegate;

- (instancetype)initWithConfiguration:(IZPaymentConfiguration *)configuration;
- (IZFuture *)start;

- (void)cancel;

@end

@interface UIViewController (PurchaseFlow)

+ (BOOL)hasOngoingPurchaseFlow;

@end


NS_ASSUME_NONNULL_END
