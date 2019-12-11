//
//  PurchaseFlow.h
//  iZettle
//
//  Created by Måns Bernhardt on 2012-03-26.
//  Copyright (c) 2012 iZettle. All rights reserved.
//

@import UIKit;
@import iZettleShared;
#import "Payment.h"
#import "ConfirmRefundController.h"

@class IZCardReader;
@class IZAccount;

NS_ASSUME_NONNULL_BEGIN

typedef void (^PushForceAudioIsReader)(void);
typedef void (^PopForceAudioIsReader)(void);

extern NSString *const PurchaseAmountKey;
extern NSString *const PurchasePaymentTypeKey;

@interface UINavigationController (PurchaseFlow)

// The future returned from paymentReferencesFunction should be a paymentReferences NSDictionary that will be passed to the payments (including  e.g. shoppingCartUUID, apiReference etc).
// The result from the returned postPaymentFunction future will be passed as the receiptDictionary if internal and purchaseInfo dictionary if external.
// The second param passed to postPaymentFunction is the paid amount for cash and CardPaymentInfo for other payments.
- (IZFuture<IZCardPaymentInfo *> *)chargeAccount:(IZAccount *)account
                                          reader:(IZCardReader *)reader
                                          amount:(NSDecimalNumber *)amount
                                   enableTipping:(BOOL)enableTipping
                              isRepeatingPayment:(BOOL)isRepeatingPayment
                       paymentReferencesFunction:(IZFuture<NSDictionary *> *(^)(void))paymentReferencesFunction
NS_SWIFT_NAME(charge(account:amount:reader:enableTipping:isRepeatingPayment:paymentReferencesFunction:));

- (IZFuture<IZCardPaymentInfo *> *)refundAccount:(IZAccount *)account
                                          amount:(NSDecimalNumber *)amount
                         retrievePaymentFunction:(IZFuture<NSDictionary *> *(^)(void))retrievePaymentFunction
                       paymentReferencesFunction:(IZFuture<NSDictionary *> *(^)(void))paymentReferencesFunction
                             postPaymentFunction:(IZFuture *(^)(CardInterface cardInterface, IZCardPaymentInfo *data))postPaymentFunction
                                         options:(RefundOptions)options
NS_SWIFT_NAME(refund(account:amount:retrievePaymentFunction:paymentReferencesFunction:postPaymentFunction:options:));


- (IZFuture *)checkMicrophone;
- (IZFuture *)checkAudioJackPreference;

@end

/*
    Purchase Flow Stages (where we are going - work in progress)
 
 
    Login
 
 
    Create Shopping Cart (could be run in parallel with select & collect). Might also sync product library before.
        OUT : shopppingCartUUID / payment references?
 
 
    Select & Collect (Runs together as user my step backwards)
 
        Select - Cash, card etc.     -> reader and paymentType

        Collect - cash change, manual entry, visa etc. -> depending on type
 
        OUT : collected data
 
 
 
    Charge Card Payment - Contact bank, signature & id
        IN: amount, payment references (shopppingCartUUID etc), collected data
        OUT: CardPaymentInfo

 
 
    Create Purchase 
        IN payments, shopping cart data etc.
        OUT receipt dictionary
 
 
 
    Send Receipt (receipt dictionary) - send receipt view. (send email, manual printing, order ticket etc). Not for SDK.
        IN amount, receipt dictionary
 
 
 */


NS_ASSUME_NONNULL_END
