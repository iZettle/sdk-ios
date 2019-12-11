//
//  IZReaderUpdateViewController.h
//  iZettlePayments
//
//  Created by Andrei Valkovskii on 2018-09-04.
//  Copyright © 2018 iZettle. All rights reserved.
//

@import iZettleShared;
@class IZReaderUpdateManager;

NS_ASSUME_NONNULL_BEGIN

@interface IZReaderUpdateViewController : FormController

- (instancetype)initWithUpdateManager:(IZReaderUpdateManager *)updateManager;

@end

NS_ASSUME_NONNULL_END
