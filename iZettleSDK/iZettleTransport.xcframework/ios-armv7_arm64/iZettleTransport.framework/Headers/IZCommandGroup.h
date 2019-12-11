//
//  IZCommandGroup.h
//  iZettleTransport
//
//  Created by Said Sikira on 2018-02-13.
//  Copyright © 2018 iZettle. All rights reserved.
//

/**
 Defines command groups available in CRONE protocol

 - IZCommandGroupGeneral: General commands related to the CRONE peripheral
 - IZCommandGroupFiles: Writing and reading files to/from device
 - IZCommandGroupSecurity: Security
 - IZCommandGroupTransaction: Transaction related commands
 - IZCommandGroupDisplay: Displaying text and bitmaps
 - IZCommandGroupLogging: Logging manipulation
 */
typedef NS_ENUM(UInt8, IZCommandGroup) {
    IZCommandGroupGeneral = 0x01,
    IZCommandGroupFiles = 0x02,
    IZCommandGroupSecurity = 0x03,
    IZCommandGroupTransaction = 0x04,
    IZCommandGroupDisplay = 0x05,
    IZCommandGroupLogging = 0x06,
    IZCommandGroupCardEvent = 0x81,
    IZCommandGroupDevicePowerEvent = 0x82,
    IZCommandGroupKeyExchange = 0x08,
    IZCommandGroupUnrecognized = 0xFF
} NS_SWIFT_NAME(CommandGroup);
