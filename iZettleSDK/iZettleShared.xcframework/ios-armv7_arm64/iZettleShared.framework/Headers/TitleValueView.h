//
//  TitleValueView.h
//  iZettle
//
//  Created by Mattias Jähnke on 2013-08-07.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import UIKit;

@class AmountLabel;
@class DingbatLabel;
@class SmallLabel;

@interface TitleValueView : UIView

@property (nonatomic, strong) SmallLabel *titleLabel;
@property (nonatomic, strong) AmountLabel *valueLabel;
@property (nonatomic, strong) DingbatLabel *dingbatLabel;

@end
