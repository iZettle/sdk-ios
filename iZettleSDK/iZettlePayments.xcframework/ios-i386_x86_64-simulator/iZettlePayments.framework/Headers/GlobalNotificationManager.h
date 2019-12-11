//
//  GlobalNotificationManager.h
//  iZettleStorePurchase
//
//  Created by Mattias Jähnke on 2013-05-21.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import UIKit;

@class IZAccount, IZFuture;

@interface GlobalNotificationManager : NSObject

@property (nonatomic, strong) UIViewController *presentFromViewController;

+ (GlobalNotificationManager *)shared;

@end
