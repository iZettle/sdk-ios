//
//  SettingsController.h
//  iZettle
//
//  Created by Mattias Jähnke on 2014-06-10.
//  Copyright (c) 2014 iZettle. All rights reserved.
//

@import iZettleShared;
#import "IZAccount.h"

NS_ASSUME_NONNULL_BEGIN

@interface IZSettingsController : AccountFormController

- (IZFuture *)presentSettings;
- (IBAction)closeSettings:(id)sender;

@end

@interface UIViewController (SettingsController)

- (UIBarButtonItem *)izSettingsBarButtonItemForAccount:(IZAccount *)account;
- (IZFuture *)izPresentSettingsControllerForAccount:(IZAccount *)account;
- (BOOL)izIsSettingsControllerPresented;

@end

NS_ASSUME_NONNULL_END
