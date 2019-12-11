//
//  CardReaderManager.h
//  iZettle
//
//  Created by Måns Bernhardt on 2012-08-07.
//  Copyright (c) 2012 iZettle. All rights reserved.
//

#import "IZCardReader.h"
#import "IZDatecsReader2Pairer.h"

NS_ASSUME_NONNULL_BEGIN

extern NSString *const CardReaderManagerAudioReaderUsageDidChangedNotification;

extern NSString *const CardReaderManagerAudioJackDidConnectNotification;
extern NSString *const CardReaderManagerAudioJackDidDisconnectNotification;

extern NSString *const CardReaderManagerRecordPermissionDeniedNotification;
extern NSString *const CardReaderManagerRecordPermissionGrantedNotification;

extern NSString *const CardReaderManagerDidStartDetectingAudioReaderNotification;
extern NSString *const CardReaderManagerDidEndDetectingAudioReaderNotification;

typedef NS_ENUM(NSInteger, AudioReaderUsage) {
    AudioReaderUsageAsk,
    AudioReaderUsageNever,
    AudioReaderUsageAlways,
};

@class IZettleNetworkContext;
@class DatecsReaderV2;
@class IZPairedDevice;
@class IZAccount;
@class IZPaymentsReachability;

@interface CardReaderManager : NSObject <IZDatecsReader2Pairer>

@property(nonatomic, class, readonly) CardReaderManager *shared;

- (void)switchToAccount:(IZAccount *)account;
- (void)clearAccount;

@property(nonatomic) BOOL isAudioReadersSupported;
@property(nonatomic) AudioReaderUsage audioReaderUsage;
@property(nonatomic) BOOL enableAudioReaders;
@property(nonatomic) BOOL audioJackIsUsedForHeadphones;

/// Call after playing movies or other audio that may have affected the audio settings.
- (void)resetAudioReadersIfNeeded;

@property(nonatomic, readonly) BOOL isAudioJackConnected;

@property(nonatomic, readonly) BOOL isDetectingAudioReaders;

@property (nonatomic, readonly) NSArray<IZCardReader *> *readers;
@property (nonatomic, readonly) IZSignal<NSArray<IZCardReader *> *> *readersSignal;

// Make sure to keep reader awake and responsive to card inserts and swipes
@property(nonatomic, assign) BOOL enableResponsiveMode;

@property (nonatomic, assign, nullable) IZCardReader *updatingCardReader; // Currently can only be one at a time due to cookies and backend transactions
@property (nonatomic, assign) BOOL isAnyReaderUpdating;

- (void)pushForceAudioIsReader;
- (void)popForceAudioIsReader;
@property (nonatomic, readonly) BOOL audioReaderIsForced;

- (DatecsReaderV2 *)readerForDevice:(IZPairedDevice *)device;

@property (nonatomic, strong, readonly) IZPaymentsReachability *reachability;

@end

@interface CardReaderManager (Utilities)

@property(nonatomic, readonly) BOOL shouldAskForAudioPreferences;

@end

@class IZPairedDeviceStore;
@class IZAccessoryListener;

// extension to make singleton testable
@interface CardReaderManager (Testing)

- (instancetype)initWithPairedDeviceStore:(IZPairedDeviceStore *)store;
@end

NS_ASSUME_NONNULL_END
