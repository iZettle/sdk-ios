//
//  AccountManager.m
//  iZettle SDK Sample
//
//  Created by Stanislav Goryachev on 2020-07-01.
//  Copyright © 2020 PayPal Inc. All rights reserved.
//

#import "AccountManager.h"

@implementation AccountManager

+ (instancetype)shared {
    static dispatch_once_t once;
    static AccountManager *_instance;

    dispatch_once(&once, ^{
        _instance = [AccountManager new];
    });

    return _instance;
}

@end
