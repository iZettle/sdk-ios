//
//  DatecsBLE.h
//  BLEmmy
//
//  Created by Mattias Jähnke on 2017-08-15.
//  Copyright © 2017 iZettle. All rights reserved.
//

@import iZettleShared;

@class CBPeripheral;
@class IZBatteryInfo;

@protocol DatecsBLEDelegate <NSObject>

- (void)didReceiveData:(NSData *)data;

- (void)didReceiveError:(NSError *)error;

@end

@interface DatecsBLE : NSObject

@property (nonatomic, readonly, class) NSArray<NSString *> *identifiers;

@property (nonatomic, weak) id<DatecsBLEDelegate> delegate;
@property (nonatomic, strong, readonly) CBPeripheral *peripheral;
@property (nonatomic, strong) NSData *key;

- (instancetype)initWithPeripheral:(CBPeripheral *)peripheral;

- (void)wakeUpDevice;

/**
 Discovers characteristics of a reader
 */
- (IZFuture *)discoverCharacteristics;
- (void)resetCharacteristics;

- (IZFuture *)writeData:(NSData *)data;

- (void)readPoweredOnCharacteristic;

/// returns distinct peripheral's power status: @YES if peripheral was powered on
/// or @NO if peripheral was powered off
@property (nonatomic, strong, readonly) IZSignal<NSNumber *> *powerSignal;

- (IZFuture<NSString *> *)readSerialNumber;
- (IZFuture<NSString *> *)readPaVersion;
- (IZFuture<NSString *> *)readFirmwareVersion;
- (IZFuture<NSString *> *)readBluetoothVersion;

- (IZFuture<IZBatteryInfo *> *)readBatteryInfo;
@property (nonatomic, strong, readonly) IZSignal<IZBatteryInfo *> *batteryInfoSignal;

@end
