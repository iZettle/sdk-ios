// 
// Copyright © 2019 iZettle. All rights reserved.
// 

@import Foundation;

@class DatecsReader;
@class IZAccount;

NS_ASSUME_NONNULL_BEGIN

@protocol IZNecessaryReaderUpdateProtocol <NSObject>

- (instancetype)initWithReader:(DatecsReader *)reader
                       account:(IZAccount *)account
                    completion:(void(^)(NSError * _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
