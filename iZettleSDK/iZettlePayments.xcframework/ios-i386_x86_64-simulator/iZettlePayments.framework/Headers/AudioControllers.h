//
//  CardReaderAudioController.h
//  iZettleStorePurchase
//
//  Created by Måns Bernhardt on 2014-11-24.
//  Copyright (c) 2014 iZettle. All rights reserved.
//

@import iZettleShared;

@interface FormController (AudioControllers)

- (IZFuture *)displayAskForAudioPreference;

@end


@interface UIViewController (AudioControllers)

- (IZFuture *)displayMicrophonePermissionNeeded;

@end

