//
//  IZTransactionTelemetry.h
//  iZettleShared
//
//  Created by Said Sikira on 5/31/17.
//  Copyright © 2017 iZettle. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IZTelemetry.h"

NS_ASSUME_NONNULL_BEGIN

@interface IZTransactionTelemetry : NSObject

+ (instancetype)shared;
- (instancetype)init NS_UNAVAILABLE;

@property (strong, atomic, readonly) NSString * paymentTrackingID;

- (void)generateNewTrackingID;

- (void)eventWithContext:(id<IZTelemetryContext>)context
                 domain:(NSString *)domain
                 subdomain:(NSString *)subdomain
                    page:(NSString *)page
                    action:(NSString *)action;

- (void)eventWithContext:(id<IZTelemetryContext>)context
                  domain:(NSString *)domain
               subdomain:(NSString *)subdomain
                    page:(NSString *)page
                  action:(NSString *)action
       additionalPayload:(NSDictionary<NSString *,NSString *> *)payload;
@end

NS_ASSUME_NONNULL_END
