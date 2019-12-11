//
//  PurchaseFlow+External.h
//  iZettleStorePurchase
//
//  Created by Mattias Jähnke on 2015-03-11.
//  Copyright (c) 2015 iZettle. All rights reserved.
//

@import iZettleShared;
#import "IZAccount.h"

NS_ASSUME_NONNULL_BEGIN

extern NSString *const APIReferenceKey;
extern NSString *const ReferreralCodeReferenceKey;

@interface UINavigationController (PurchaseFlowExternal)

- (IZFuture *)chargeExternalAccount:(nullable IZAccount *)account
                             amount:(NSDecimalNumber *)amount
                      enableTipping:(BOOL)enableTipping
                 paymentReferences:(NSDictionary *)paymentReferences;

- (IZFuture *)refundExternalAccount:(nullable IZAccount *)account
                             amount:(nullable NSDecimalNumber *)amount
                          reference:(NSString *)reference
                   refundReferences:(NSDictionary *)refundReferences;


@end


@interface UIViewController (PurchaseFlowExternal)

+ (BOOL)isPresentingExternalFlow;

// Will login if needed and handle logout notifications to go back to login
- (IZFuture *)presentExternalFlowUsingAccount:(nullable IZAccount *)account
                          enforcedUserAccount:(nullable NSString *)enforcedUserAccount
                                usingFunction:(IZFuture *(^)(UINavigationController *nc, IZAccount *account))function;

@end

@interface IZAccount (QueryPaymentInfo)

- (IZFuture<NSDictionary *> *)paymentInfoWithReference:(NSString *)reference;

@end

NS_ASSUME_NONNULL_END
