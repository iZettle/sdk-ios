// 
// Copyright © 2019 iZettle. All rights reserved.
// 

@import UIKit;

@class IZCardPaymentInfo;
@class IZPaymentManager;
@class IZFuture<T>;

NS_ASSUME_NONNULL_BEGIN

@interface IZPaymentViewController : UIViewController

- (instancetype)initWithPaymentManager:(IZPaymentManager *)paymentManager;

- (IZFuture<IZCardPaymentInfo *> *)charge;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
