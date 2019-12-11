//
//  IZSession.h
//  iZettleStorePurchase
//
//  Created by Mattias Jähnke on 2015-05-26.
//  Copyright (c) 2015 iZettle. All rights reserved.
//

@import Foundation;
@import CoreData;
@import UIKit;
@import iZettleShared;

NS_ASSUME_NONNULL_BEGIN

extern NSString *const IZAccountCancelBackgroundNetworkOperationsNotification;

extern NSString *const IZActiveAccountWillChangeNotification;
extern NSString *const IZActiveAccountDidChangeNotification;
extern NSString *const IZOldAccountKey;
extern NSString *const IZNewAccountKey;

// Called after a revist if any backend data was updated.
extern NSString *const IZAccountDidUpdateNotification;

// Called if a the active account was change or updated
extern NSString *const IZActiveAccountDidChangeOrWasUpdatedNotification;

extern NSString *const IZBetaFeatureNewLogin;
extern NSString *const IZBetaFeatureInventory;
extern NSString *const IZBetaFeatureCashRegisterWithdrawal;
extern NSString *const IZBetaFeatureTipping;
extern NSString *const IZBetaFeatureDetached;

@class CashDenominations, IZettleNetworkContext, IZAccount;

// Consider splittin IZAccount into two, a base that is not logged in (does not have networkcontext etc) and one that is logged in. Split knownAccounts into two as well.
// Both should be completly imutable... hence no properties nor methods should change it's state.
// If something has to changes such as after a revist, create new account and put the old one out of "known accounts"....
// By following above, potential user holding on to an account in process or vc wont ever get unexpected changes.
// It would be great if backend supported logging out to make sure if something continues to access a users context or a copy of it after the user been logged out, that it would result in an invalid session.

@interface IZAccount : NSManagedObject
+ (nullable IZAccount *)initiateAccounts; // Will initiate the accounts and set the current account (if any) and call IZActiveAccount[Will/Did]ChangeNotification. Only allowed to be called once

+ (nullable NSString *)lastUsedUserEmail;

+ (BOOL)switchToAccount:(nullable IZAccount *)account error:(NSError **)error;
+ (IZFuture *)switchToAccount:(nullable IZAccount *)account;
+ (void)removeAccount:(IZAccount *)account;

#ifdef DEBUG
+ (void)setCurrentAccount:(nullable IZAccount *)account;
#endif

// Will login user.. make sure to also call switch to change user
+ (IZFuture<IZAccount *> *)loginWithEmailAddress:(NSString *)emailAddress
                                        password:(NSString *)password
                                 oneTimePassword:(nullable NSString *)oneTimePassword;

+ (IZFuture<IZAccount *> *)loginAsUserUuid:(NSString *)userUuid withAdminEmailAddress:(NSString *)emailAddress password:(NSString *)password oneTimePassword:(NSString * _Nullable)oneTimePassword;

+ (IZFuture<IZAccount *> *)loginWithOneTimeToken:(NSString *)oneTimeToken;

// TODO Should be private! (this will eliminate the problem of making IZOAuthToken public and available to Swift)
+ (IZFuture<IZAccount *> *)fetchAccountWithOAuthToken:(NSData *)oauthToken;

+ (IZFuture *)resetPasswordForAccountWithEmail:(NSString *)email;

- (void)addElevatedOAuthToken:(NSData *)oauthToken;

- (IZFuture *)revisit; // Only for logged in user... should be a class method as it might create a new user...

- (void)logoutButDontSwitchUser; // will logout user but don't set current user to nil if self is current

- (void)logout;
- (IZFuture *)logoutWithConfirmationOnViewController:(UIViewController *)viewController;
- (IZFuture *)logoutWithConfirmationOnViewController:(UIViewController *)viewController title:(NSString *)title message:(nullable NSString *)message;

// return an int with the format MMmmr (ex. 4110 for version 4.11.0) reprensenting the version of the last migration
+ (UInt16)version;
@property(readonly) UInt16 version;
@property (readonly) NSDictionary *payload;

@property(readonly) BOOL hasSession; // Remove if we split up in logged in and out users
@property(readonly) NSDate *lastDateActive;

@property(readonly, nullable) NSDictionary *userInfo NS_REFINED_FOR_SWIFT; // Make private?
@property(readonly, nullable) NSDictionary *organizationSettings NS_REFINED_FOR_SWIFT; // Make private?
@property(readonly, nullable) NSString *userInfoHash; // Make private?
@property(readonly, nullable) NSDictionary *cardPaymentConfig; // Make private?

@property(readonly, nullable) NSDictionary *transactionConfig; // Make private?
@property(readonly, nullable) NSString *transactionConfigHash; // Make private?

@property(readonly, nullable) CashDenominations *cashDenominators NS_REFINED_FOR_SWIFT;
@property(readonly) NSString *terminalLanguageIdentifier NS_REFINED_FOR_SWIFT;

@property(readonly) IZettleNetworkContext *networkContext;

@property(readonly) NSString *userIdentifier NS_REFINED_FOR_SWIFT;

@property(readonly) BOOL supportsTipping;
@property(readonly) BOOL supportsBackgroundUpdate;
@property(readonly) BOOL supportsContactlessAnimation;
@property(readonly) BOOL supportsDeprecatedReaderMessage;
@property(readonly) BOOL supportsReaderSelection;

@property(readonly) NSDecimalNumber *gratuityAmountMaxPercentage;

// protected

- (void)accountDidUpdate;
- (void)accountBecameActive:(BOOL)firstTime;

- (BOOL)validateNewPayload:(NSDictionary *)newPayload oldPayload:(nullable NSDictionary *)oldPayload error:(NSError **)error;
- (void)handleDialogPayload:(NSDictionary *)newPayload;

- (void)bumpVersion;
- (void)purgeSessionCache;

- (IZFuture<NSString *> *)retrieveOneTimeToken;

@property (nonatomic, strong) NSURL *baseURL;

@property (readonly, class) NSArray<IZAccount*> *knownAccounts;

@end

@interface IZAccount (Utilities)

- (IZFuture<NSDictionary *> *)supportDictionaryShouldDisplayErrorAlert:(BOOL)shouldDisplayErrorAlert;
- (BOOL)useFeatureNamed:(NSString *)name NS_REFINED_FOR_SWIFT;
- (BOOL)useBetaFeatureNamed:(NSString *)name NS_REFINED_FOR_SWIFT;
- (NSSet<NSString *> *)betaFeatures;
+ (void)clearAllAccounts;
@end

@protocol IZAccountHolder <NSObject>

@property (nonatomic, nullable) IZAccount *account NS_REFINED_FOR_SWIFT;

@end

@interface NSObject (AccountHolder)

- (void)izSetAccount:(nullable IZAccount *)account;
- (nullable IZAccount *)izAccount;

@end

@interface NSArray (AccountHolder)

- (void)izSetAccount:(nullable IZAccount *)account;
- (nullable IZAccount *)izAnyAccount;

@end

@interface UINavigationController (AccountHolder) <IZAccountHolder>
@end

@interface UISplitViewController (AccountHolder) <IZAccountHolder>
@end

@interface AccountViewController : LocalizedViewController<IZAccountHolder>
@end

@interface AccountFormController : FormController<IZAccountHolder>
@end

@interface IZAccount (IZTelemetryContext) <IZTelemetryContext>
@end

NS_ASSUME_NONNULL_END
