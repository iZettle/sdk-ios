//
//  IZPairingChallenge.h
//  iZettlePayments
//
//  Created by Andrei Valkovskii on 2018-07-26.
//  Copyright © 2018 iZettle. All rights reserved.
//

#import <iZettleShared/iZettleShared.h>
#import "DatecsReaderQueue+KeyExchange.h"
#import "IZDatecsReader2Pairer.h"

@class DatecsReaderV2;

NS_ASSUME_NONNULL_BEGIN

@interface IZPairingChallenge : NSObject

- (instancetype)initWithPairing:(id<IZDatecsReader2Pairer>)pairing;

- (IZFuture<NSString *> *)startPairing;

- (IZFuture *)inititateDisplayCheck;

- (IZFuture<DatecsReaderBondResultValue> *)waitForNumericalComparisonResult;

- (IZSignal *)waitForNumericalComparisonResultSignal;

- (IZFuture *)finishNumericalComparison:(DatecsReaderBondResult)result;

// --

+ (instancetype)new  NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

@interface IZPairingChallenge (Resolving)
- (void)didConnectReader:(DatecsReaderV2 *)reader;
- (void)didDisconnectReaderWithError:(NSError *)error;

- (IZFuture<NSData *> *)waitForKey;
- (IZFuture *)agreeToUseKey:(NSData *)key;
@end

NS_ASSUME_NONNULL_END
