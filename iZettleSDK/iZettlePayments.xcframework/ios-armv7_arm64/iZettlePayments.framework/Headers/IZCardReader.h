//
//  Reader.h
//  iZettle
//
//  Created by Måns Bernhardt on 2012-08-07.
//  Copyright (c) 2012 iZettle. All rights reserved.
//

@import Foundation;
@import iZettleShared;
#import "IZTippingType.h"
#import "IZCardReaderModel.h"
#import "IZBatteryInfo.h"

NS_ASSUME_NONNULL_BEGIN

extern NSString *const CardReaderDidConnectNotification;
extern NSString *const CardReaderDidDisconnectNotification;

extern NSString *const CardReaderCardStatusDidUpdateNotification;
extern NSString *const CardReaderCardStatusKey;

extern NSString *const CardReaderBatteryStatusDidUpdateNotification;

extern NSString *const CardReaderActivePaymentInterfacesChangedNotification;

extern NSString *const CardReaderPinEntryStateChangedNotification;
extern NSString *const CardReaderPinEntryDigitCountChangedNotification;

extern NSString *const CardReaderUpdateAvailabilityChangedNotification;
extern NSString *const CardReaderUpdateAvailabilityKey; // Boolean
extern NSString *const CardReaderUpdateNecessaryKey;
extern NSString *const CardReaderUpdateStateChangedNotification;

typedef NS_ENUM(NSUInteger, PinEntryState) {
    PinEntryStateNone,
    PinEntryStateInProgress,
    PinEntryStateInProgressLastAttempt,
    PinEntryStateDone,
    PinEntryStateFailed,
};

typedef NS_ENUM(NSUInteger, CardReaderUpdateState) {
    CardReaderUpdateStateNone,
    CardReaderUpdateStateDownloadingFilesFromServer,
    CardReaderUpdateStateUploadingFilesToReader,
    CardReaderUpdateStateConfiguringReader,
    CardReaderUpdateStateRebootingReader,
    CardReaderUpdateStateSuccessful,
    CardReaderUpdateStateFailed,
};

typedef NS_ENUM(NSUInteger, CardReaderInterface) {
    CardReaderInterfaceAudioJack,
    CardReaderInterfaceBluetooth,
};


typedef NS_ENUM(NSUInteger, CardInterface) {
    CardInterfaceChip = 1,
    CardInterfaceSwipe,
    CardInterfaceContactless,
};

typedef NS_ENUM(NSUInteger, IZConnectionStatus) {
    IZConnectionStatusDisconnected,
    IZConnectionStatusSleeping,
    IZConnectionStatusConnected,
};

typedef NS_ENUM(NSUInteger, IZConfigurationState) {
    IZConfigurationStateNotConfigured,
    IZConfigurationStateConfiguring,
    IZConfigurationStateConfigured,
    IZConfigurationStateConfigurationFailed
};

typedef NS_ENUM(NSUInteger, IZCardReaderColor) {
    IZCardReaderColorUnknown = 0,
    IZCardReaderColorLight,
    IZCardReaderColorDark,
    IZCardReaderColorOcean,
};

@class IZCardReaderQueue, IZReaderNetworkContext;

@interface CardStatus : NSObject

@property (readonly, assign) CardInterface cardInterface;
@property (readonly, copy) NSData *cardData; // might be nil, but it cardError is nil it's a valid insert, swipe or tap
@property (readonly, strong) NSError *cardError; // if not nil, insert, swipe or tap failed.

/// A string that is used for tracking
- (NSString *)cardInterfaceString;

@end

@interface IZCardReader : NSObject

- (instancetype)initWithReaderQueue:(IZCardReaderQueue *)queue networkContext:(IZReaderNetworkContext *)networkContext;

+ (instancetype)new  NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@property (nonatomic, strong, readonly) IZFutureQueue *backendOperationQueue;

@property (nonatomic, readonly) IZCardReaderModel readerModel;
@property (nonatomic, readonly) NSString *readerModelName;
@property (nonatomic, readonly) NSString *readerName;
@property (nonatomic, readonly) NSString *readerIdentifier;
@property (nonatomic, readonly) NSString *displayableReaderName;

@property (nonatomic, copy, readonly) NSString *smallIconName;
@property (nonatomic, copy, readonly) NSString *mediumIconName;
@property (nonatomic, copy, readonly) NSString *largeIconName;
@property (nonatomic, copy, readonly) NSString *cardIconName;

// We set this property for v1 and Miura readers to match IZAccessoryService
// when we handle accessory disconnect event
@property (nonatomic, readonly) NSString *accessorySerialNumber;

@property (nonatomic, readonly) CardReaderInterface interface;
@property (nonatomic, readonly) float preferredAudioVolume;

@property (nonatomic, readonly) BOOL isChargeable; // defaults to false
@property (nonatomic, readonly) BOOL hasPinEntry; // defaults to false
@property (nonatomic, readonly) BOOL hasHardwarePinSound; // defaults to false
@property (nonatomic, readonly) BOOL isPoweredDown;
@property (nonatomic, readonly) BOOL lastFirmwareUpdateAvailability; // defaults to false - contains a cached answer from the last check

- (BOOL)isCardInterfaceSupported:(CardInterface)interface;
- (BOOL)isCardInterfaceActive:(CardInterface)interface;

@property (nonatomic, readonly, getter=isContactlessEnabled) BOOL contactlessEnabled;

// Make sure to keep reader awake and responsive to card inserts and swipes
@property (nonatomic, assign) BOOL enableResponsiveMode;

@property (nonatomic, copy, nullable, readonly) NSDecimalNumber *chargeAmount;
- (void)chargeAmount:(NSDecimalNumber * _Nullable)amount isSCA:(BOOL)isSCA;

@property (nonatomic, readonly, nullable) CardStatus *cardStatus; // If nil no card inserted, swiped or tapped.

@property (nonatomic, readonly) PinEntryState pinEntryState;
@property (nonatomic, readonly) NSInteger pinEntryDigitCount;

@property (nonatomic) IZCardReaderQueue *queue;

//// Reader update state
@property (readonly) CardReaderUpdateState updateState;
@property (readonly) NSInteger updateStageCount;
@property (readonly) NSInteger updateStageIndex;
@property (readonly) float updateProgress; // 0-1 or INFINITY
@property (strong, nullable) NSError *updateError;
@property (readonly) BOOL isUpdateInProgress;

- (void)confirmUpdateDone; // call if state is success or failure to leave update state (typically from a user confirm action or timeout).

- (IZFuture *)downloadAndApplySoftwareUpdate;

// PIN bypass

@property (atomic, readonly) BOOL isPinBypassEnabled;
- (void)setPinBypassEnabled:(BOOL)pinBypassEnabled;

// connection status

@property (nonatomic, assign) IZConnectionStatus connectionStatus NS_REFINED_FOR_SWIFT;
- (IZSignal<NSNumber *> *)connectionStatusSignal NS_REFINED_FOR_SWIFT;

// device info

- (IZFuture<NSString *> *)serialNumber NS_REFINED_FOR_SWIFT;

- (IZFuture<NSString *> *)paVersion NS_REFINED_FOR_SWIFT;

- (IZFuture<NSString *> *)firmwareVersion NS_REFINED_FOR_SWIFT;

- (IZFuture<NSString *> *)bluetoothVersion NS_REFINED_FOR_SWIFT;

- (IZCardReaderColor)readerColor NS_REFINED_FOR_SWIFT;

- (IZFuture<NSString *> *)versionDescription;

- (IZFuture <NSNumber *> *)cachedReaderSoftwareUpdate NS_REFINED_FOR_SWIFT;

// battery info

@property (nonatomic, readonly) IZBatteryStatus batteryStatus NS_REFINED_FOR_SWIFT;

/// Emits battery status events with values corresponding to `IZBatteryStatus` enum
///
/// @see `IZBatteryStatus`
- (IZSignal<NSNumber *> *)batteryStatusSignal NS_REFINED_FOR_SWIFT;

- (IZFuture<NSNumber *> *)checkBatteryPercentage NS_REFINED_FOR_SWIFT;

- (void)resetCache;

@property (nonatomic, assign) IZConfigurationState configurationState NS_REFINED_FOR_SWIFT;
@property (nonatomic, strong) IZSignal<NSNumber *> *configurationStateSignal NS_REFINED_FOR_SWIFT;
@property (nonatomic, strong, nullable) NSError *configurationError;

- (void)markAsNeedingConfiguration;
- (void)updateConfigurationIfNeeded;

@end

@interface IZCardReader (Utilities)

- (IZFuture *)waitForCardRemoval;
- (IZFuture *)waitForCardRemovalOrICCFailed;
- (void)updateAudioVolume;

@end


typedef NS_ENUM(NSUInteger, CardReaderDisplayText) {
    CardReaderDisplayTextUpdatingReader,
    CardReaderDisplayTextInsertCardOrSwipe,
    CardReaderDisplayTextInsertCard,
    CardReaderDisplayTextReady, // insert or swipe or both depending on card reader
    CardReaderDisplayTextReadingCard,
    CardReaderDisplayTextCardOK,
    CardReaderDisplayTextCardHasChip,
    CardReaderDisplayTextAuthorizing,
    CardReaderDisplayTextIdentification,
    CardReaderDisplayTextSignature,
    CardReaderDisplayTextApprovedRemoveCard,
    CardReaderDisplayTextApproved,
    CardReaderDisplayTextReceipt,
    CardReaderDisplayTextAbortedRemoveCard,
    CardReaderDisplayTextAborted,
    CardReaderDisplayTextCardNotRead,
    CardReaderDisplayTextPleaseWait,
    CardReaderDisplayTextAmountTooHigh,
    CardReaderDisplayTextAmountTooLow,
    CardReaderDisplayTextIdleMode
};


typedef NS_ENUM(NSUInteger, ReaderOperationType) {
    ReaderOperationTypeChipCharge,
    ReaderOperationTypeChipSignature,
    ReaderOperationTypeChipFinalize,

    ReaderOperationTypeSwipeCharge,
    ReaderOperationTypeSwipeSignature,
    ReaderOperationTypeSwipeFinalize,

    ReaderOperationTypeContactlessCharge,
    ReaderOperationTypeContactlessSignature,
    ReaderOperationTypeContactlessFinalize,

    
    ReaderOperationTypeAbort,
    
    ReaderOperationTypeCheckConfiguration,
    ReaderOperationTypeConfiguration,
    ReaderOperationTypeKeyInject,
    
    ReaderOperationTypeFirmwareUpdate,
};

@class Attempt;

@interface IZCardReaderQueue : IZFutureQueue

@property (nonatomic, readonly) IZCardReader *reader;
@property (readonly) IZReaderNetworkContext *networkContext;


- (IZFuture *)queueFunction:(IZFuture *(^)(id queue))function timeout:(NSTimeInterval)timeout retryCount:(NSInteger)retryCount;

// FIXME: make private +>
- (IZFuture<NSString *> *)serialNumber;
- (IZFuture<NSNumber *> *)checkBattery; // BatteryStatus
- (IZFuture<NSNumber *> *)checkBatteryPercentage; // Battery percentage

- (IZFuture<NSString *> *)versionDescription; // Combined types of versions
- (IZFuture<NSString *> *)paymentApplicationVersionDescription;
- (IZFuture<NSString *> *)firmwareVersionDescription;
- (IZFuture<NSString *> *)bluetoothVersionDescription;
// <+

#pragma mark Tipping

/**
 Checks if tipping is supported

 @return `IZFuture` with `NSNumber` (0 or 1) indicating wheter tipping functionality is supported
 */
- (IZFuture<NSNumber *> *)supportsTippingWithType:(IZTippingType)tippingType;

/**
 Initiates tipping flow on the card reader
 
 @note Readers without tipping functionality should return `CardReaderErrorTippingNotSupported` error.

 @param amount Starting amount
 @param tippingType Type of tipping flow
 @param timeout Timeout (in seconds)
 @return Total amount (initial amount + tip amount)
 */
- (IZFuture<NSDecimalNumber *> *)captureGratuityStartingWithAmount:(NSDecimalNumber *)amount
                                                       tippingType:(IZTippingType)tippingType
                                             minimumTippingVersion:(NSString *)minimumTippingVersion
                                                           timeout:(NSTimeInterval)timeout;

/**
 Cancel the ongoing gratuity flow
 @note Should only be called during gratuity flow
 */
- (IZFuture *)cancelOngoingGratuityFlow;

- (IZFuture *)displayReaderText:(CardReaderDisplayText)text;

- (IZFuture *)displayCurrentCardStatus;

// Payments
- (nullable NSString *)mobilePathForOperation:(ReaderOperationType)operation;
- (IZFuture<NSDictionary *> *)initialPayloadForOperation:(ReaderOperationType)operation;
- (IZMutableURLRequest *)urlRequestForOperation:(ReaderOperationType)operation payload:(NSDictionary *)payload isInitial:(BOOL)isInitial;

- (NSUInteger)estimatedProgressCountForOperation:(ReaderOperationType)operation;

- (IZFuture<NSData *> *)sendBackendReaderCommand:(NSString *)command;

// Config and update
- (nullable IZFuture *)checkConfigurationAndUpdateIfNeeded;
- (nullable IZFuture *)checkForFirmwareUpdate;
- (nullable IZFuture *)downloadAndApplySoftwareUpdate;

- (nullable IZFuture *)readSystemLogUsingProgressBlock:(void (^)(NSUInteger byteCount))progressBlock;

// Call before updateReaderUpdateState after for notification to trigger to update ui..
- (void)updateStageIndex:(NSInteger)stageIndex stageCount:(NSInteger)stageCount;
- (void)updateReaderUpdateState:(CardReaderUpdateState)state;
- (void)updateReaderUpdateState:(CardReaderUpdateState)state progress:(float)progress;

- (nullable IZFuture *)runReaderUpdateUsingFunction:(IZFuture *(^)(id queue))function;

/// Emits battery status events with values corresponding to `IZBatteryStatus` enum
///
/// @see `IZBatteryStatus`
- (IZSignal<NSNumber *> *)batteryStatusSignal NS_REFINED_FOR_SWIFT;

@end


extern NSString *const CardReaderErrorDomain;

typedef NS_ERROR_ENUM(CardReaderErrorDomain, CardReaderErrorCode) {
    CardReaderErrorCodeCardNotPresent,
    CardReaderErrorCodeReaderNotPresent,
    CardReaderErrorCodeTimeout,
    CardReaderErrorCodeMicrophonePermissionNeeded,
    CardReaderErrorCodeUserCancelled,
    CardReaderErrorCodeLinkLost,
    CardReaderErrorCodeInvalidState,
    CardReaderErrorCodeLinkTimeout,
    CardReaderErrorCodeLinkNotReady,
    CardReaderErrorCodeUnknownResponse,
    CardReaderErrorCodeCancelled,
    CardReaderErrorCodeCardNotRead,
    CardReaderErrorCodeOperationFailed,
    CardReaderErrorCodeSwipedCardHasChip,
    CardReaderErrorCodeSwipeCardNotRead,
    CardReaderErrorCodeChipCardNotRead,
    CardReaderErrorCodeContactlessCardNotRead,
    CardReaderErrorCodeTippingNotSupported,
    CardReaderErrorCodeTippingSoftwareUpgradeNeeded,
};

@interface NSError (IZCardReader)

+ (NSString * _Nullable)_readerErrorTitleForCode:(CardReaderErrorCode)code;
+ (NSString *)_readerErrorMessageForCode:(CardReaderErrorCode)code;

+ (instancetype)cardReaderErrorWithCode:(CardReaderErrorCode)code userInfo:(NSDictionary * _Nullable)info;
+ (instancetype)cardReaderErrorWithCode:(CardReaderErrorCode)code;
- (BOOL)isCardReaderErrorWithCode:(CardReaderErrorCode)code;

@end

NS_ASSUME_NONNULL_END




