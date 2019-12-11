//
//  IZBatteryLevel.h
//  iZettlePayments
//
//  Created by Andrei Valkovskii on 2018-08-27.
//  Copyright © 2018 iZettle. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, IZBatteryStatus) {
    IZBatteryStatusNoBattery,
    IZBatteryStatusUnknown,
    IZBatteryStatusGood,
    IZBatteryStatusBad,
    IZBatteryStatusCharging
};

@interface IZBatteryInfo : NSObject

@property (nonatomic, readonly) BOOL isCharging;
@property (nonatomic, readonly) BOOL isCableConnected;
@property (nonatomic, readonly) UInt8 percentage;
@property (nonatomic, readonly) IZBatteryStatus status;

- (instancetype)initWithIsCharging:(BOOL)isCharging
                  isCableConnected:(BOOL)isCableConnected
                        percentage:(UInt8)percentage
                            status:(IZBatteryStatus)status;

+ (instancetype)unknownInfo;

@end
