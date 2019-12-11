//
//  NSData+IZCrypto.h
//  iZettleTransport
//
//  Created by Karl-Johan Drougge on 2018-03-22.
//  Copyright © 2018 iZettle. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

extern NSErrorDomain const IZCryptoErrorDomain;

typedef NS_ERROR_ENUM(IZCryptoErrorDomain, IZCryptoErrorCode) {
    IZCryptoErrorCodeOperationFailed,
    IZCryptoErrorCodeInvalidKeySize
} NS_SWIFT_NAME(CryptoError);

extern NSUInteger const IZCryptoNonceLength;

/**
 Calculates padding length for given block size and input length
 
 @note For block ciphers, input data needs to be padded until the input is divisible
 by block length.
 
 For example, if we use AES 128 CBC blocks need have size of 128 bits or 16 bytes. If we
 want to encrypt data with lenght of 30, we would have to pad it with 2 bytes (two blocks
 of 16 bytes).
 
 @param blockSize Block size
 @return Number of bytes
 */
NSUInteger iz_paddingLength(NSUInteger blockSize,
                            NSUInteger inputLength)
NS_SWIFT_NAME(paddingLength(blockLength:inputLength:));

/**
 Implements cryptographic operations
 */
@interface NSData (IZCrypto)

#pragma mark Digest

/**
 Returns a `SHA256` digest of `self`
 */
- (NSData *)iz_sha256 NS_SWIFT_NAME(sha256());

#pragma mark Encryption, Decryption

/**
 Encrypts `self` using AES CBC cipher
 
 @param key Key material
 @param error Error pointer
 
 @warning Passing a key that is not 256 bits long will result in error
 
 @return `NSData` object with encrypted bytes
 */
- (nullable NSData *)iz_aes256EncryptedWithKey:(NSData *)key
                                         error:(NSError * _Nullable *)error NS_SWIFT_NAME(aes256Encrypted(with:));

/**
 Decrypts `self` using AES CBC cipher
 
 @param key Key material
 @param error Error pointer
 
 @warning Passing a key that is not 256 bits long will result in error
 
 @return `NSData` object with decrypted bytes
 */
- (nullable NSData *)iz_aes256DecryptedWithKey:(NSData *)key
                                         error:(NSError * _Nullable *)error NS_SWIFT_NAME(aes256Decrypted(with:));

/**
 The first three bytes of encrypted 32 byte zero-block using self as an encryption key

 @param error Encryption error
 @return return KCV
 */
- (nullable NSData *)iz_kcv:(NSError * _Nullable *)error NS_SWIFT_NAME(kcv());


/**
 Generate 128-bit secure random nonce

 @return NSData object with random nonce
 */
+ (instancetype)iz_nonce NS_SWIFT_NAME(nonce());

@end

NS_ASSUME_NONNULL_END
