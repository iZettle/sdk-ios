//
//  iZettleTransport+BLESpecification.h
//  iZettleTransport
//
//  Created by Said Sikira on 2018-05-29.
//  Copyright © 2018 iZettle. All rights reserved.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

/**
 f4(PKa, PKb, Nx, Z) from Bluetooth Core 4.2, Vol 3, PartH, 2.2.6
 
 @remark Z is fixed to 8 bits of zeros and the parameter is ommited
 
 The output of the function is defined as:
    f4(U, V, X, Z) = AES-CMAC[X] (U || V || Z)
 
 Where `X` is the key material
 */
NSData * iz_f4(NSData * pkA,
               NSData * pkB,
               NSData * nonce)
NS_SWIFT_NAME(f4(pkA:pkB:nonce:));

/**
 g2(PKa, PKb, Na, Nb) from Bluetooth Core 4.2, Vol 3, PartH, 2.2.9
 
 The output of the function is defined as:
    Compare Value = g2 (U, V, X, Y) mod 10^6 (the six least significant digits of the 32-bit integer g2)

    The g2 function is defined as g2(U, V, X, Y) = AES-CMAC[X] (U || V || Y) mod (2^32)
    Where `X` is the key material
 */
NSString * iz_g2(NSData *pkA,
                 NSData *pkB,
                 NSData *nA,
                 NSData *nB)
NS_SWIFT_NAME(g2(pkA:pkB:nA:nB:));

NS_ASSUME_NONNULL_END
