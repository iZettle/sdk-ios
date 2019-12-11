//
//  DatabaseManager.h
//  iZettle
//
//  Created by Mattias Jähnke on 2012-10-31.
//  Copyright (c) 2012 iZettle. All rights reserved.
//

@import Foundation;
@import CoreData;

NS_ASSUME_NONNULL_BEGIN

// Can't be move to swift yet so it ended up here

@interface IZDatabaseManager : NSObject
@property(class, readonly) IZDatabaseManager *shared;

- (NSURL *)storeURL;
- (void)purgeStore;

@property(readonly) BOOL needMigration;

- (NSManagedObjectModel *)managedObjectModel;
- (NSPersistentStoreCoordinator *)persistentStoreCoordinator;
- (NSManagedObjectContext *)managedObjectContext;

- (NSDictionary<NSString *, id> * __nullable)metaDataWithKey:(NSString *)key error:(NSError **)error;
- (BOOL)saveMetaData:(NSDictionary<NSString *, id> *)metaData withKey:(NSString *)key error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
