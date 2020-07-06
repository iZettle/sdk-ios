//
//  AccountManager.h
//  iZettle SDK Sample
//
//  Created by Stanislav Goryachev on 2020-07-01.
//  Copyright © 2020 iZettle. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface AccountManager : NSObject

@property(nonatomic, strong, nullable) NSString *enforcedUserAccount;

+ (instancetype)shared;

@end

NS_ASSUME_NONNULL_END
