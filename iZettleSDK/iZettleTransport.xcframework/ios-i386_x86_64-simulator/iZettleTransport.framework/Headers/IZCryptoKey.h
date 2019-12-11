//
//  IZCryptoKey.h
//  iZettleTransport
//
//  Created by Andrei Valkovskii on 2018-03-26.
//  Copyright © 2018 iZettle. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(CryptoKey)
@interface IZCryptoKey : NSObject

- (instancetype)initWithKeyRef:(SecKeyRef)key;

- (nullable instancetype)initPublicKeyWithData:(NSData *)data error:(NSError * _Nullable *)error;

- (SecKeyRef)keyRef;

/**
 Exports key. the format follows the ANSI X9.63 standard using a byte string of 04 || X || Y.

 @return key as sequence of bytes
 */
- (nullable NSData *)dataRepresentation:(NSError * _Nullable *)error;


/**
 Exports key in compressed format: N || X where N (first byte) is
 02 for even values of y and 03 for odd values).

 @param error data convertion error
 @return key data in compressed format
 */
- (nullable NSData *)compressed:(NSError * _Nullable *)error;

@end

NS_ASSUME_NONNULL_END
