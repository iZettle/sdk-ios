//
//  IZReaderUpdateFlow.h
//  iZettlePayments
//
//  Created by Andrei Valkovskii on 2018-11-03.
//  Copyright © 2018 iZettle. All rights reserved.
//

@import iZettleShared;

@class DatecsReader;
@class IZAccount;

NS_ASSUME_NONNULL_BEGIN

// FIXME: necessary update flow
@interface IZReaderUpdateFlow : NSObject

- (IZFuture *)startPaymentFlowWithReader:(DatecsReader *)reader
                                 account:(IZAccount *)account
                     presentationContext:(UIViewController *)presentationContext;

- (IZFuture<IZPair<UIViewController *, IZFuture *> *> *)startPairingFlowWith:(IZAccount *)account;

@end

NS_ASSUME_NONNULL_END
