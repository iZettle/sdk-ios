//
//  IZBaseReaderUpdateViewController.h
//  iZettlePayments
//
//  Created by Andrei Valkovskii on 2018-09-04.
//  Copyright © 2018 iZettle. All rights reserved.
//

@import iZettleShared;

@interface IZBaseReaderUpdateViewController : FormController

@property (nonatomic, strong) NSString *titleMessage;
@property (nonatomic, strong) NSString *subtitleMessage;

@property (nonatomic, strong, readonly) IZFuture *future;

- (IZFuture *)displayWithOperationFuture:(IZFuture *)future title:(NSString *)title confirmWhenDone:(BOOL)confirmWhenDone;

@end
