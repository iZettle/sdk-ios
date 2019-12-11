//
//  IZSupportWriteCaseController.h
//  iZettleStorePurchase
//
//  Created by Mattias Jähnke on 2015-04-21.
//  Copyright (c) 2015 iZettle. All rights reserved.
//

@import iZettleShared;
#import "IZAccount.h"

@interface IZCaseMailComposerController : AccountViewController

@property (nonatomic, copy) NSArray *pathArray; // Array of "key":"value"
@property (nonatomic, copy) NSArray *attachments; // Array of IZMultipartPart

- (IZFuture *)composeEmail;

@end
