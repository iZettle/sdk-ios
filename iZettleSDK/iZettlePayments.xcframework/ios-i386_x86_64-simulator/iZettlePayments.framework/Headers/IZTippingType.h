//
//  IZGratuityType.h
//  iZettlePayments
//
//  Created by Said Sikira on 2018-02-05.
//  Copyright © 2018 iZettle. All rights reserved.
//

/**
 IZTippingType will distinguish the different tipping flows we support
 */
typedef NS_ENUM(NSUInteger, IZTippingType) {
    IZTippingTypeTotalAmount,
    IZTippingTypeExtraAmount
};
