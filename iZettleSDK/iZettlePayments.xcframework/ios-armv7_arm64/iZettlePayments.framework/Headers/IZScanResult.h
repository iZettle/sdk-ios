//
//  IZCoreBluetoothAdvertisingData.h
//  iZettlePayments
//
//  Created by avv on 2018-05-17.
//  Copyright © 2018 iZettle. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CBPeripheral;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(UInt8, IZAdvertisingPowerState) {
    IZAdvertisingPowerStateOff = 0,
    IZAdvertisingPowerStateOn = 1 << 0
} NS_SWIFT_NAME(AdvertisingPowerState);

typedef NS_ENUM(UInt8, IZAdvertisingColorCode) {
    IZAdvertisingColorCodeLight = 0,
    IZAdvertisingColorCodeDark  = 1 << 0,
    IZAdvertisingColorCodeOcean = 1 << 1
} NS_SWIFT_NAME(AdvertisingColorCode);

@interface IZAdvertismentData : NSObject

@property (nonatomic, assign, readonly) NSInteger RSSI;
@property (nonatomic, assign, readonly) IZAdvertisingPowerState powerState;
@property (nonatomic, assign, readonly) IZAdvertisingColorCode colorCode NS_REFINED_FOR_SWIFT;

- (instancetype)initWithRSSI:(NSInteger)RSSI manufacturerData:(NSData *)data;

@end

@interface IZScanResult : NSObject

@property (nonatomic, strong, readonly) IZAdvertismentData *adverismentData;
@property (nonatomic, strong, readonly) CBPeripheral *peripheral;

- (instancetype)initWithPeripheral:(CBPeripheral *)peripheral RSSI:(NSInteger)RSSI manufacturerData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
