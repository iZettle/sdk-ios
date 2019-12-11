//
//  HerdAttemptCoordinator+iZettle.h
//  iZettleStorePurchase
//
//  Created by Mattias Jähnke on 2015-01-22.
//  Copyright (c) 2015 iZettle. All rights reserved.
//

@import Foundation;
@import iZettleShared;

NS_ASSUME_NONNULL_BEGIN

@class IZAccount;

@interface IZettleHerd : Herd

+ (instancetype)dynamicEndpoint;
+ (instancetype)productionEndpoint;

- (void)paymentOperationalStatusForCountryCode:(NSString *)countryCode completion:(void(^)(BOOL operational, NSError *error))completion;

@end

/*!
 IZettleHerdAttempt will automatically report itself to herd once considered successful or failed
 */
@interface IZettleHerdAttempt : Attempt

+ (instancetype)attemptWithType:(NSString *)type account:(IZAccount *)account;

@end

NS_ASSUME_NONNULL_END
