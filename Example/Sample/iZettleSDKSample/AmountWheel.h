//
//  AmountWheel.h
//  iZettle SDK Sample
//
//  Copyright © 2015 PayPal Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef void (^AmountUpdateBlock)(NSDecimalNumber *amount);

@interface AmountWheel : UIImageView

@property (nonatomic, readonly) NSDecimalNumber *amount;
@property (nonatomic, copy) AmountUpdateBlock amountUpdatedBlock;

@end
