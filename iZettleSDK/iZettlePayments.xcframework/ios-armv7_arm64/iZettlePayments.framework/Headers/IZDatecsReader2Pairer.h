//
//  IZDatecsReader2Pairer.h
//  iZettlePayments
//
//  Created by Andrei Valkovskii on 2019-02-05.
//  Copyright © 2019 iZettle. All rights reserved.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

@class DatecsReaderV2;

@protocol IZDatecsReader2Pairer <NSObject>
- (void)pairReader:(DatecsReaderV2 *)reader;
- (void)unpairReader:(DatecsReaderV2 *)reader;
@end

NS_ASSUME_NONNULL_END
