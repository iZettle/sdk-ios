//
//  IZAccessoryService+EAAccessory.h
//  iZettlePayments
//
//  Created by Andrei Valkovskii on 2018-06-14.
//  Copyright © 2018 iZettle. All rights reserved.
//

#import "IZAccessoryService.h"

@class EAAccessory;

@interface IZAccessoryService (EAAccessory)

- (instancetype)initWithAccessory:(EAAccessory *)accessory protocol:(NSString *)protocol error:(NSError **)error;

- (BOOL)hasSameEAAccessory:(IZAccessoryService *)service;

@end
