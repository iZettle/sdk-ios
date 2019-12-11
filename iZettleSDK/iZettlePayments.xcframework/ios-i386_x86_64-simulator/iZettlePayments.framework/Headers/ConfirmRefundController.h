//
//  ConfirmRefundController.h
//  iZettleStorePurchase
//
//  Created by Mattias Jähnke on 2015-03-09.
//  Copyright (c) 2015 iZettle. All rights reserved.
//

@import iZettleShared;

typedef NS_OPTIONS(NSUInteger, RefundOptions) {
    RefundOptionUseExtendedConfirmation = 1<<0,
    RefundOptionEnableSettings = 1<<1,
};

@class IZAccount;

@interface ConfirmRefundController : FormController

@property (nonatomic, readonly) IZFuture *cancelFuture;

// Returns password inputted by user (NSString)
- (IZFuture<NSString *> *)confirmRefundingPayment:(NSDictionary *)paymentDetails
                                 overridingAmount:(NSDecimalNumber *)overridingAmount
                                          account:(IZAccount *)account
                                          options:(RefundOptions)options;

@end
