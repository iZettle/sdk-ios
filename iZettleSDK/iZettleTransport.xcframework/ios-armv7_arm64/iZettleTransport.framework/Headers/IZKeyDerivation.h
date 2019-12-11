//
//  IZKeyDerivation.h
//  iZettleTransport
//
//  Created by Said Sikira on 2018-05-29.
//  Copyright © 2018 iZettle. All rights reserved.
//
@import Foundation;

NS_ASSUME_NONNULL_BEGIN

/**
 Performs simple Hashed Message Authentication Code
 (HMAC)-based key derivation function.
 
 @remark Uses SHA-256 digest
 
 @see https://tools.ietf.org/html/rfc5869
 
 @param length Length of output keying material in octets (<= 255*HashLen)
 @param IKM Input keying material
 @param salt Salt value (a non-secret random value);
 @param info Optional context and application specific
 information (can be a zero-length binary)
 
 @return OKM - Output keying material (of length octets)
 */
NSData * iz_hkdf(NSUInteger length,
                 NSData * IKM,
                 NSData * salt,
                 NSData * info)
NS_SWIFT_NAME(hkdf(length:IKM:salt:info:));

/**
 Computes the encryption key (shared secret key) using derive function `iz_hkdf` on DHKey

 @param key DHKey
 @return shared secret key
 */
NSData *iz_deriveKey(NSData *key) NS_SWIFT_NAME(derive(key:));

NS_ASSUME_NONNULL_END
