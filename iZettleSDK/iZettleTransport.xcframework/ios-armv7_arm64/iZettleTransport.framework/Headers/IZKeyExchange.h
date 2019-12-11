//
//  IZKeyExchange.h
//  iZettleTransport
//
//  Created by Andrei Valkovskii on 2018-03-26.
//  Copyright © 2018 iZettle. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class IZCryptoKey;

NS_SWIFT_NAME(KeyExchange)
@interface IZKeyExchange : NSObject

- (instancetype)initWithPrivateKey:(IZCryptoKey *)privateKey;

- (void)setPublicKey:(IZCryptoKey *)publicKey;

- (nullable NSData *)generateSharedSecretWithError:(NSError * _Nullable *)error;

@end

NS_ASSUME_NONNULL_END
