//
//  Payment.h
//  Payment
//
//  Created by Måns Bernhardt on 2015-10-09.
//  Copyright © 2015 iZettle. All rights reserved.
//

@import Foundation;

//! Project version number for Payment.
FOUNDATION_EXPORT double iZettlePaymentsVersionNumber;

//! Project version string for Payment.
FOUNDATION_EXPORT const unsigned char iZettlePaymentsVersionString[];

// In this header, you should import all the public headers of your framework
// using statements like #import <iZettlePayments/PublicHeader.h>

// Used by SDK & GoApp +>
#import <iZettlePayments/IZAccount.h>
#import <iZettlePayments/Payment.h>

#import <iZettlePayments/GlobalNotificationManager.h>
#import <iZettlePayments/CardReaderManager.h>
#import <iZettlePayments/IZettleTranslationsDataSource.h>

#import <iZettlePayments/PurchaseFlow.h>
#import <iZettlePayments/PurchaseFlow+External.h>

#import <iZettlePayments/IZBaseReaderUpdateViewController.h>
#import <iZettlePayments/IZSettingsController.h>

#import <iZettlePayments/UIApplication+Utilitites.h>
#import <iZettlePayments/NSBundle+iZettlePayments.h>
#import <iZettlePayments/NSError+PaymentsSDK.h>
#import <iZettlePayments/NSError+Account.h>
// <+

// Used by GoApp only +>

// Payment flow
#import <iZettlePayments/IZPaymentConfiguration.h>
#import <iZettlePayments/IZPaymentManager.h>
#import <iZettlePayments/IZPaymentViewController.h>

// Refund
#import <iZettlePayments/ConfirmRefundController.h> // Why do we need to expose it to go app?

// Readers
#import <iZettlePayments/IZCardReader.h>
#import <iZettlePayments/DatecsReader.h>
#import <iZettlePayments/DatecsReaderV2.h>
#import <iZettlePayments/DatecsReaderQueue+KeyExchange.h>


#import <iZettlePayments/IZDatecsReader2Pairer.h>
#import <iZettlePayments/IZPairingChallenge.h>
#import <iZettlePayments/IZPairedDevice.h>
#import <iZettlePayments/IZCardReaderModel.h>
#import <iZettlePayments/IZBatteryInfo.h>
#import <iZettlePayments/IZTippingType.h>

#import <iZettlePayments/IZPeripheralLink.h>
#import <iZettlePayments/IZAccessoryListener.h>
#import <iZettlePayments/IZAccessoryService.h>
#import <iZettlePayments/IZAccessoryServiceError.h>
#import <iZettlePayments/IZCoreBluetoothListener.h>
#import <iZettlePayments/IZScanResult.h>
#import <iZettlePayments/DatecsBLE.h>

#import <iZettlePayments/IZReaderUpdateManager.h>
#import <iZettlePayments/IZReaderUpdateViewController.h>
#import <iZettlePayments/IZReaderUpdateFlow.h>
#import <iZettlePayments/IZBackgroundUpdate.h>
#import <iZettlePayments/IZNecessaryReaderUpdateProtocol.h>
#import <iZettlePayments/IZBackgroundUpdateScheduler.h>

#import <iZettlePayments/IZettleNetworkContext.h>

#import <iZettlePayments/CashDenominations.h>

#import <iZettlePayments/IZTokenManager.h>
#import <iZettlePayments/IZettleOAuthToken.h>
#import <iZettlePayments/OAuthTokenScope.h>
#import <iZettlePayments/NSURL+OAuth.h>

#import <iZettlePayments/IZettleHerd.h>
#import <iZettlePayments/IZLocationManager.h>
#import <iZettlePayments/IZDatabaseManager.h>

#import <iZettlePayments/IZSupportArticleListController.h>
#import <iZettlePayments/IZCaseMailComposerController.h>
#import <iZettlePayments/AudioControllers.h>

#import <iZettlePayments/CachedDateFormatter.h>
#import <iZettlePayments/IZAccount+Properties.h>
#import <iZettlePayments/NSError+iZettleRequests.h>
#import <iZettlePayments/NSDateFormatter+Utilities.h>
#import <iZettlePayments/UIImage+Backend.h>
// <+
