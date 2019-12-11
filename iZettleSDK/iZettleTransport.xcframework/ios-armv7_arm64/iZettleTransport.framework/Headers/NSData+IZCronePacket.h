//
//  NSData+IZCronePacket.h
//  iZettleTransport
//
//  Created by Andrei Valkovskii on 2018-02-27.
//  Copyright © 2018 iZettle. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// Crone transport layer packet error domain
NS_SWIFT_NAME(CronePacketErrorDomain)
extern NSErrorDomain const IZCronePacketErrorDomain;

/**
 Defines errors that can occur during serialization and deserialization
 of CRONE transport layer packets.
 */
typedef NS_ERROR_ENUM(IZCronePacketErrorDomain, IZCronePacketErrorCode) {
    IZCronePacketErrorCodeZeroLength,
    IZCronePacketErrorCodeChecksumMismatch,
    IZCronePacketErrorCodeInvalidLength,
    IZCronePacketErrorCodeInvalidResponseStatus,
    IZCronePacketErrorCodeInvalidSHA,
    IZCronePacketErrorInvalidPacket,
    IZCronePacketErrorCodeEncryptionError = 0x2d,
    IZCronePacketErrorCodeInvalidKeyError = 0x19,
} NS_SWIFT_NAME(CronePacketError);

/**
 Defines format of the packet
 
 - IZPacketTypePlain: Plain format, bytes are represented in clear text
 - IZPacketTypeEncrypted: Encrypted format, some bytes are encrypted
 */
typedef NS_ENUM(UInt8, IZPacketType) {
    IZPacketTypePlain = 0x00,
    IZPacketTypeEncrypted = 1 << 7
};

/**
 Provides interface for serialization and deserialization of CRONE packets
 
 ## CRONE Packet structure
 
 | Header                               | Transport Payload                                            |
 +----------+---------+--------+--------+--------+--------+--------+------------+---------+------------+----------+
 | Start(1) | Type(1) | RFU(2) | LEN(2) | SEQ(2) | SID(4) | LEN(2) | V1 Payload | Padding | SHA256(32) | Checksum |
 +----------+---------+--------+--------+--------+--------+--------+------------+---------+------------+----------+
 | Included in SHA256                   |                                                 |            |
 +----------------------------------------------------------------------------------------+            |
 |                                      | Encrypted                                                    |
 |                                      +--------------------------------------------------------------+
 | Included in Checksum                                                                                |
 +-----------------------------------------------------------------------------------------------------+
 
 */
@interface NSData (IZCronePacket)

#pragma mark Serialization

/**
 Constructs a CRONE packet with plain type
 
 @param payload V1 payload
 @param error Error pointer
 @return `NSData` object conforming to plain transport protocol
 */
+ (nullable instancetype)plainCronePacketWithPayload:(NSData *)payload
                                               error:(NSError * _Nullable *)error
NS_SWIFT_NAME(plainCronePacket(with:));

///**
// Constructs a encrypted CRONE packet with given key
//
// @param payload V1 payload
// @param key Encryption key material
// @param error Error pointer
// @return `NSData` object conforming to encrypted transport protocol
// */
+ (nullable instancetype)encryptedCronePacketWithPayload:(NSData *)payload
                                                     key:(NSData *)key
                                                   error:(NSError * _Nullable *)error
NS_SWIFT_NAME(encryptedCronePacket(with:key:));

#pragma mark Deserialization

/**
 Deserializies plain CRONE packet and extracts crone data.
 
 @param error Error pointer
 @return `IZCroneData`
 */
- (nullable NSData *)croneDataWithError:(NSError * _Nullable *)error;

/**
 Deserializies encrypted CRONE packet with given key.
 
 @param key Encryption key
 @param error Error pointer
 @return `IZCroneData`
 */
- (nullable NSData *)croneDataWithKey:(NSData *)key
                                     error:(NSError * _Nullable *)error
NS_SWIFT_NAME(croneData(with:));

#pragma mark Helper methods

/**
 Checks if data is valid complete or incoplete crone packet. This method doesn't
 validate packet body or whether the data form a complete CRONE packet.
 Data with zero length is considered as valid.
 */
- (BOOL)isValidPartialCronePacketWithError:(NSError * _Nullable *)error;

/**
 Checks if `self` is a complete CRONE packet
 */
@property (nonatomic, readonly) BOOL isCompleteCronePacket;

/**
 Validates that the checksum of the provided data is equal to
 the calculated checksum of same data
 
 @note Passed data should contain checksum in last byte
 
 @param data Input data
 @param error Error pointer
 @return Boolean indicating whether checksum is valid
 */
- (BOOL)iz_validateChecksumForData:(NSData *)data
                             error:(NSError *_Nullable *)error
NS_SWIFT_NAME(validateChecksum(for:));
@end

NS_ASSUME_NONNULL_END
