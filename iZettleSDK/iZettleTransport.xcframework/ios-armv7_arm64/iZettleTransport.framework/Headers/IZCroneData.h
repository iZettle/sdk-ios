//
//  IZCroneData.h
//  iZettleTransport
//
//  Created by Said Sikira on 2018-02-13.
//  Copyright © 2018 iZettle. All rights reserved.
//

#import "Foundation/Foundation.h"
#import "IZCommandGroup.h"

NS_ASSUME_NONNULL_BEGIN

/// Crone transport layer packet error domain
extern NSErrorDomain const IZCroneDataErrorDomain;

/**
 Defines errors that can occur during serialization and deserialization
 of CRONE transport layer packets.
 */
typedef NS_ERROR_ENUM(IZCroneDataErrorDomain, IZCroneDataErrorCode) {
    IZCroneDataErrorCodeZeroLength,
    IZCroneDataErrorCodeInvalidStatus,
    IZCroneDataErrorCodeInvalidLength,
    IZCroneDataErrorCodeChecksumMismatch,
    IZCroneDataErrorCodeUnrecognizedCommand
} NS_SWIFT_NAME(CroneDataError);


/**
 Describes data structure used to construct commands based on the CRONE protocol.
 */
NS_SWIFT_NAME(CroneData)
@interface IZCroneData : NSObject

#pragma mark Properties

/**
 Sequence number
 */
@property (atomic, readonly) UInt8 sequenceNumber;

/**
 Command group
 */
@property (atomic, readonly) IZCommandGroup commandGroup;

/**
 Command ID
 */
@property (atomic, readonly) UInt8 command;

/**
 Data information part. TLV encoded.
 */
@property (atomic, readonly) NSData *data;

/**
 Command status. Fixed to 0x00 when issuing commands
 */
@property (atomic, readonly) UInt8 status;

/**
 Constructs a `NSData` object that follows Crone protocol
 */
@property (atomic, strong, readonly) NSData *payload;

#pragma mark Initilizers

- (instancetype)initWithCommandGroup:(IZCommandGroup)commandGroup
                                command:(UInt8)command
                                   data:(NSData *)data
                         sequenceNumber:(UInt8)sequenceNumber;

/**
 Constructs `IZCronePayload` from CRONE accessory response

 @param payload Accessory response
 @return Instance of `IZCronePayload`
 */
- (nullable instancetype)initWithResponsePayload:(NSData *)payload error:(NSError * _Nullable *)error;

- (instancetype)init NS_UNAVAILABLE;
@end

NS_ASSUME_NONNULL_END;
