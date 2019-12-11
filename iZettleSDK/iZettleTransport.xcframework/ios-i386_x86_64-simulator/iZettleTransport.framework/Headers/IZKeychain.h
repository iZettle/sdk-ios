//
//  IZKeychain.h
//  iZettleTransport
//
//  Created by Andrei Valkovskii on 2018-03-22.
//  Copyright © 2018 iZettle. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

extern NSErrorDomain const IZKeychainErrorDomain;

typedef NS_ERROR_ENUM(IZKeychainErrorDomain, IZKeychainErrorCode) {
    IZKeychainErrorCodeGeneric,
} NS_SWIFT_NAME(KeychainError);


NS_SWIFT_NAME(Keychain)
@interface IZKeychain : NSObject

- (instancetype)initWithUserIdentifier:(NSString *)identifier;

#pragma mark - working with data

/**
 Adds data into keychain for the key. If `data` param is nil then method tries to
 remove data for given key

 @param data data to add into keychain
 @param key key
 @param error error if keychain failed for some reson. Ideally this should never happen
 @return YES if success, NO and error if there was an error
 */
- (BOOL)insertData:(nullable NSData *)data forKey:(NSString *)key error:(NSError * _Nullable *)error;

/**
 Removes data from keychain for specified key

 @param key key
 @param error error if keychain failed for some reson. Ideally this should never happen
 @return YES if success, NO and error if there was an error
 */
- (BOOL)removeDataForKey:(NSString *)key error:(NSError * _Nullable *)error;

/**
 Fetches data from keychain for given key

 @param key key
 @param error error if keychain failed for some reson. Ideally this should never happen
 @return Data if success, nil if nothing found
 */
- (nullable NSData *)fetchDataForKey:(NSString *)key error:(NSError * _Nullable *)error;

#pragma mark - clean up

- (void)clear;

@end

NS_ASSUME_NONNULL_END
