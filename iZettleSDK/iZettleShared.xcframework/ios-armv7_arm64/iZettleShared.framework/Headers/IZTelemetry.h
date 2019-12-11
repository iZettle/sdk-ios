//
//  IZTelemetry.h
//  iZettleShared
//
//  Created by Hans Sjunnesson on 07/04/16.
//  Copyright © 2016 iZettle. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IZFuture.h"

/// Main `Payments` telemetry domain
extern NSString * _Nonnull const IZPaymentsTrackingDomain;

NS_ASSUME_NONNULL_BEGIN

@protocol IZTelemetryContext
@required

@property (nonnull, readonly) NSString * trackingBaseURL;
@property (nonnull, readonly) NSString * authorization;

@end


/// Generic tracking base url used in comparison for the special case of the generic telemtry context.
extern NSString * const IZGenericTrackingBaseURL;

/// A `IZTelemetryContext` which allows for generic TelemetryEvents, which simply do not include user id.
@interface IZGenericTelemetryContext: NSObject<IZTelemetryContext>

/// Returns a shared instance.
+ (instancetype)sharedInstance;

@end


typedef void (^IZTelemetryEventHandler)(
  id<IZTelemetryContext> _Nonnull context,
  NSString * _Nonnull domain,
  NSString * _Nonnull subdomain,
  NSString * _Nonnull page,
  NSString * _Nullable action,
  NSDictionary<NSString *, NSObject *> * _Nullable payload);


/// A class which handles persisting and sends telemetry events.
@interface IZTelemetry : NSObject

+ (void)registerHandler:(_Nonnull IZTelemetryEventHandler)handler;

/// Registers a telemetry event.
/// \param domain: The main domain of the event.
/// \param subdomain: The subdomain of the main domain event.
+ (void)eventWithContext:(_Nonnull id<IZTelemetryContext>)context domain:(NSString * _Nonnull)domain subdomain:(NSString * _Nonnull)subdomain page:(NSString * _Nonnull)page;

/// Registers a telemetry event.
/// \param domain: The main domain of the event.
/// \param subdomain: The subdomain of the main domain event.
/// \param action: The action of the event.
+ (void)eventWithContext:(_Nonnull id<IZTelemetryContext>)context domain:(NSString * _Nonnull)domain subdomain:(NSString * _Nonnull)subdomain page:(NSString * _Nonnull)page action:(NSString * __nullable)action;

/// Registers a telemetry event with a payload.
/// \param domain: The main domain of the event.
/// \param subdomain: The subdomain of the main domain event.
/// \param action: The action of the event.
/// \param payload: The key value payload of the event.
+ (void)eventWithContext:(_Nonnull id<IZTelemetryContext>)context domain:(NSString * _Nonnull)domain subdomain:(NSString * _Nonnull)subdomain page:(NSString * _Nonnull)page action:(NSString * __nullable)action payload:(NSDictionary<NSString *, NSString *> * __nullable)payload;

@end


@interface IZFuture (Scope)

/// Returns a scoped IZFuture. See scope(...)
/// \param name: The name of the stope
/// \param future: The IZFuture
+ (IZFuture *)scopeWithName:(NSString *)name future:(IZFuture *)future;

@end

NS_ASSUME_NONNULL_END
