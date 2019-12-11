//
//  IZPairedDevice.h
//  iZettlePayments
//
//  Created by Andrei Valkovskii on 2018-04-26.
//  Copyright © 2018 iZettle. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IZCardReader.h"

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(PairedDevice)
@interface IZPairedDevice : NSObject <NSCoding>

@property (nonatomic, strong, readonly) NSString *identifier; // TODO: maybe use serial number instead
@property (nonatomic, strong, readonly) NSString *name;
@property (nonatomic, strong, readonly) NSString *type;
@property (assign, readonly) IZCardReaderColor color;
@property (nonatomic, strong) NSData *key;

- (instancetype)initWithIdentifier:(NSString *)identifier
                              name:(NSString *)name
                              type:(NSString *)type
                             color:(IZCardReaderColor)color;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
