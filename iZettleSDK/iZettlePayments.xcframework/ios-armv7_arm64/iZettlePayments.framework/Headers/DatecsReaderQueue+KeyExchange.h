//
//  DatecsReader+KeyExchange.h
//  iZettlePayments
//
//  Created by Said Sikira on 2018-05-30.
//  Copyright © 2018 iZettle. All rights reserved.
//

#import "DatecsReader.h"
@import iZettleShared;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(UInt8, IZNonceType) {
    IZNonceTypeDefault = 0x03,
    IZNonceTypeConfirmation = 0x02
};

/**
 Defines result of numeric comparison check on the reader

 - DatecsReaderBondResultOK: User confirmed the code
 - DatecsReaderBondResultTimeout: Code comparison timeout
 - DatecsReaderBondResultInternalError: Internal reader error
 - DatecsReaderBondResultCodeRejected: User rejected the code
 */
typedef NS_ENUM(UInt8, DatecsReaderBondResult) {
    DatecsReaderBondResultOK = 0x00,
    DatecsReaderBondResultTimeout = 0x09,
    DatecsReaderBondResultInternalError = 0x10,
    DatecsReaderBondResultCodeRejected = 0x012
};

typedef NSNumber * DatecsReaderBondResultValue;

@interface DatecsReaderQueue (KeyExchange)

/**
 Produces a signal when user interacts with numeric comparison
 check on the reader.

 `DatecsReaderBondResultValue` will contain one of the defined
 `DatecsReaderBondResult` cases.

 @see DatecsReaderBondResult
 */
@property (nonatomic, strong, readonly) IZSignal<DatecsReaderBondResultValue> *completePairingEventSignal;

- (IZFuture *)agreeToUseKey:(NSData *)key;

- (IZFuture<NSData *> *)exchangePublicKeys:(NSData *)publicKey;

- (IZFuture<NSData *> *)exchangeNonce:(NSData *)nonce type:(IZNonceType)nonceType;

/**
 Initiates numeric comparison check on the reader.

 @remark Future will complete immediatelly as the command response
 doesn't contain any data
 */
- (IZFuture *)initiateDisplayCheck;

- (IZFuture<DatecsReaderBondResultValue> *)waitForNumericalComparisonResult;

- (IZFuture *)finalizeBond:(DatecsReaderBondResult)status kcv:(NSData *)kcv;

@end

NS_ASSUME_NONNULL_END
