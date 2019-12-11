//
//  DatecsReaderV2.h
//  iZettlePayments
//
//  Created by Andrei Valkovskii on 2018-08-23.
//  Copyright © 2018 iZettle. All rights reserved.
//

#import "DatecsReader.h"

NS_ASSUME_NONNULL_BEGIN

@class IZPairingChallenge, IZPairedDevice;

@interface DatecsReaderV2 : DatecsReader

@property (nonatomic, strong, readonly) IZPairedDevice *pairedDevice;
@property (nonatomic, strong, readonly) IZPairingChallenge *challenge;

- (instancetype)initWithNetworkContext:(IZReaderNetworkContext *)networkContext
                          pairedDevice:(IZPairedDevice *)pairedDevice
                      pairingChallenge:(IZPairingChallenge *)challenge;

- (void)wakeUp;

- (void)enteredForeground;

@end

NS_ASSUME_NONNULL_END
