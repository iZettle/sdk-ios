// 
// Copyright © 2019 iZettle. All rights reserved.
// 

@import Foundation;

@class IZAccount;
@class IZFuture<T>;

typedef IZFuture<NSDictionary *> *_Nullable(^IZPaymentReference)(void);

NS_ASSUME_NONNULL_BEGIN

@interface IZPaymentConfiguration : NSObject

@property (nonatomic, strong, readonly) IZAccount *account;
@property (nonatomic, strong, readonly) NSDecimalNumber *amount;
@property (nonatomic, copy, readonly) IZPaymentReference paymentReference;
@property (nonatomic, assign, readonly) BOOL enableTipping;
@property (nonatomic, assign, readonly) BOOL isRepeatingPayment;

- (instancetype)initWithAccount:(IZAccount *)account
                         amount:(NSDecimalNumber *)amount
               paymentReference:(IZPaymentReference)paymentReference
                  enableTipping:(BOOL)enableTipping
             isRepeatingPayment:(BOOL)isRepeatingPayment;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
