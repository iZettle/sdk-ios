//
//  IZAccessoryService.h
//  iZettleStorePurchase
//
//  Created by Mattias Jähnke on 2015-09-24.
//  Copyright © 2015 iZettle. All rights reserved.
//

#import "IZPeripheralLink.h"

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(AccessoryService)
@interface IZAccessoryService: NSObject <IZPeripheralLink>

@property(nonatomic, strong, readonly) NSString *protocol;
@property(nonatomic, strong, readonly) NSString *serialNumber;

@end

NS_ASSUME_NONNULL_END
