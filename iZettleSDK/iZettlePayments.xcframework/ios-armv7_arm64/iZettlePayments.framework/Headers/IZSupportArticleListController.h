//
//  IZSupportArticleListController.h
//  iZettleStorePurchase
//
//  Created by Mattias Jähnke on 2015-04-14.
//  Copyright (c) 2015 iZettle. All rights reserved.
//

@import iZettleShared;
#import "IZAccount.h"

@interface IZSupportArticleListController : AccountFormController

@property (nonatomic, strong) NSDictionary *articleListDictionary;
@property (nonatomic, copy) IZSupportArticleListController*(^viewControllerCreationBlock)(void);
@property (nonatomic, copy) void(^composerSentBlock)(UIViewController *presentingViewController); // This block should contain dismissal/pop-logic for when an email from the composer is sent
@property (nonatomic, strong) NSMutableArray *pathArray; // Array of NSDictionary {"key":…, "value":…}
@property (nonatomic, strong) NSArray *attachments;

@end
