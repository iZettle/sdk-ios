//
//  AmountWheel.h
//  iZettle SDK Sample
//
//  Copyright (c) 2015 iZettle. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef void (^AmountUpdateBlock)(NSDecimalNumber *amount);

@interface AmountWheel : UIImageView

@property (nonatomic, readonly) NSDecimalNumber *amount;
@property (nonatomic, copy) AmountUpdateBlock amountUpdatedBlock;

@end
