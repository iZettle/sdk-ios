//
//  NSData+Encryption.h
//  iZettle
//
//  Created by Mattias Jähnke on 2013-04-09.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import Foundation;

@interface NSData (Encryption)

- (SecKeyRef)publicKeyFromCryptoCertificateData;
- (NSData *)encryptDataUsingKey:(SecKeyRef)publicKey;

- (NSData *)md5Data;
- (NSData *)sha1Data;

- (NSData *)encryptWithKey:(NSString *)key;
- (NSData *)decryptWithKey:(NSString *)key;

- (NSData *)AES256EncryptWithKey:(NSString *)key;
- (NSData *)AES256DecryptWithKey:(NSString *)key;

@end


@interface NSString (Encryption)

- (NSString *)encryptWithKey:(NSString *)key;
- (NSString *)decryptWithKey:(NSString *)key;

@end