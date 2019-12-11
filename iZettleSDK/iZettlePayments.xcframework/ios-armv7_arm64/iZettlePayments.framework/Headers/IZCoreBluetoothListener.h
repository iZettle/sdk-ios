//
//  CoreBluetoothListener.h
//  iZettlePayments
//
//  Created by Mattias Jähnke on 2017-08-14.
//  Copyright © 2017 iZettle. All rights reserved.
//

#import <iZettleShared/iZettleShared.h>
#import <CoreBluetooth/CoreBluetooth.h>

@class IZScanResult;

NS_ASSUME_NONNULL_BEGIN

typedef NSNumber * CBManagerStateValue;

NS_SWIFT_NAME(CoreBluetoothListener)
@interface IZCoreBluetoothListener: NSObject

/**
 Signals changes in the `CBCentralManager` state based on `CBManagerState` values
 */
@property (nonatomic, strong, readonly) IZSignal<CBManagerStateValue> *stateSignal NS_REFINED_FOR_SWIFT;

/**
 Returns current state of the `CBCentralManager` object
 */
@property (nonatomic, assign, readonly) CBManagerState state;

- (IZSignal<NSSet<IZScanResult *> *> *)startScanningWithIdentifiers:(NSArray<NSString *> *)identifiers NS_REFINED_FOR_SWIFT;

- (IZFuture<CBPeripheral *> *)discoverPeripheralWithId:(NSString *)identifier name:(NSString *)name peripheralServiceIdentifiers:(NSArray<NSString *> *)identifiers;
- (IZFuture<CBPeripheral *> *)connectPeripheral:(CBPeripheral *)peripheral;
- (void)disconnectPeripheral:(CBPeripheral *)peripheral;

- (IZFuture<NSError *> *)onDisconnectPeripheral:(CBPeripheral *)peripheral;

@end

NS_ASSUME_NONNULL_END
