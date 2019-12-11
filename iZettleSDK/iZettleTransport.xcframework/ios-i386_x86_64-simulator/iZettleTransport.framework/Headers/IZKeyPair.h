//
//  IZKeyPair.h
//  iZettleTransport
//
//  Created by Andrei Valkovskii on 2018-03-26.
//  Copyright © 2018 iZettle. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class IZCryptoKey;

NS_SWIFT_NAME(KeyPair)
@interface IZKeyPair : NSObject

@property (nonatomic, strong, readonly) IZCryptoKey *private;
@property (nonatomic, strong, readonly) IZCryptoKey *public;

+ (nullable instancetype)generatePairWithIdentifier:(NSString *)identifier error:(NSError * _Nullable *)error;

@end

NS_ASSUME_NONNULL_END
