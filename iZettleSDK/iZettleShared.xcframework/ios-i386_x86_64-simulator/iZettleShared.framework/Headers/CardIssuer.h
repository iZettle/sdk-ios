//
//  CardIssuer.h
//  iZettle
//
//  Created by Måns Bernhardt on 2011-08-22.
//  Copyright 2011 Babel Studios. All rights reserved.
//

@import UIKit;


typedef NS_ENUM(NSUInteger, CardIssuerType) {
    CardIssuerAmericanExpress,
    CardIssuerDiners,
    CardIssuerJcb,
    CardIssuerMastercard,
    CardIssuerVisa,
    CardIssuerMaestro,
    CardIssuerElectron,
    CardIssuerVPay,
    CardIssuerDiscovery,
    CardIssuerEC,
    CardIssuerELV,
    CardIssuerCash,
    CardIssuerOther
};


@interface CardIssuer : NSObject {}

@property (strong, nonatomic, readonly) NSString *cardName;
@property (nonatomic, readonly) NSUInteger digitCount;
@property (nonatomic, readonly) NSUInteger partialPanDigitCount;
@property (strong, nonatomic, readonly) NSString *securityCodeTitle;
@property (nonatomic, readonly) NSUInteger securityCodeCount;
@property (strong, nonatomic, readonly) NSIndexSet *dividerPositions;
@property (nonatomic, readonly) CardIssuerType cardIssuerType;

- (id)initWithInfo:(NSDictionary *)info;

- (NSString *)obfuscatedNumberFromLastDigits:(NSString *)lastDigits;
- (NSString *)obfuscatedNumberFromLastDigits:(NSString *)lastDigits usingCharacter:(NSString *)character;
- (NSString *)formattedObfuscatedNumber:(NSString *)pan;

+ (NSArray<CardIssuer *> *)allIssuers;
+ (CardIssuer *)defaultIssuer;
+ (CardIssuer *)cashIssuer;
+ (CardIssuer *)issuerWithName:(NSString *)name;
+ (CardIssuer *)issuerWithBackendKey:(NSString *)key;
+ (CardIssuer *)issuerForCardNumber:(NSString *)number;

@end


@interface CardIssuer (Additions)

- (NSString*)dingbat;

@end


@interface NSString (Issuer)

- (NSString *)panLastNonObfuscatedDigits;

@end

