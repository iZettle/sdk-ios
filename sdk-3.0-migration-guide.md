# SDK 3.0 Migration Guide

This document aims to outline the new features in the new v3.0.0 SDK release, and the changes that are required to implement them.

**Table of Contents:**

- [SDK 3.0 Migration Guide](#sdk-30-migration-guide)
  - [What's New in the SDK 3.0](#whats-new-in-the-sdk-30)
    - [Support for OAuth 2.0](#support-for-oauth-20)
      - [Get started with new Developer Portal](#get-started-with-new-developer-portal)
      - [Deprecation of API keys](#deprecation-of-api-keys)
      - [Required API changes](#required-api-changes)
        - [iOS 9 & iOS 10 support](#ios-9--ios-10-support)
    - [Support for XCFrameworks](#support-for-xcframeworks)
      - [Reduced number of frameworks](#reduced-number-of-frameworks)
      - [Deprecating Carthage support](#deprecating-carthage-support)
  - [New Public APIs](#new-public-apis)
    - [`iZettleSDKAuthorizationProvider` protocol](#izettlesdkauthorizationprovider-protocol)
    - [`iZettleSDKAuthorizationProviderError`](#izettlesdkauthorizationprovidererror)

## What's New in the SDK 3.0

### Support for OAuth 2.0

The main change implemented in the new iZettle SDK is the support for secure authorisation through OAuth 2.0. Previously, authorisation and authentication in the iZettle SDK behaved pretty much like a black box—SDK managed the process completely by itself and integrators had no way of controlling or influencing that process. While easy to use, this had a few downsides:

- Poor seller experience — Sellers routinely had to maintain two logins—one for their POS app and one for the iZettle SDK. Switching accounts between them was not a great experience either since it often happen that sellers only change their POS app account and not their SDK account.
- Poor partner experience — Partners had no way of controlling or knowing which users are logged in the SDK since all interaction with the SDK was always done by the sellers.

New SDK aims to solve these problems by implementing support for OAuth 2.0 specification. Implementing support for this protocol means that partners now have opportunity to customise and tailor authorisation experience for their sellers which in many cases improves the seller experience—e.g. no need for two logins. In addition to this, SDK sellers will now also be able to authorise/login with their PayPal accounts .

#### Get started with new Developer Portal

To get started, create a developer account in the [iZettle Developer Portal](https://developer.izettle.com/) and create an iOS SDK developer application. As part of process, you'll need to provide a callback url (URL Scheme) that needs to be defined in your application's Xcode project. Follow Apple's [Defining a Custom URL Scheme for Your App](https://developer.apple.com/documentation/uikit/inter-process_communication/allowing_apps_and_websites_to_link_to_your_content/defining_a_custom_url_scheme_for_your_app) guide to create a callback URL for your application.

After completing the process, you'll be issued a client ID that represents your developer application. Save the issued Client ID and the provided callback URL as they will be needed to initialize the SDK.

#### Deprecation of API keys

SDK 3.0 deprecates usage of the API keys that were previously required for SDK integrations. Because of this, SDK will no longer need to accept API key as part of the SDK initialization process.

#### Required API changes

The new SDK implements breaking API changes as part of the OAuth support and deprecation of API keys. SDK now needs to be intialized with an object that conforms to `iZettleSDKAuthorizationProvider` protocol. **The default implementation of this protocol is implemented by the `iZettleSDKAuthorization` class that accepts Client ID and callback URL.**

```diff
- // Initialize the SDK with the API key
- iZettleSDK.shared().start(with: "API-KEY")

+ // Initialize the SDK with authorization provider
+ do {
+   let authenticationProvider = try iZettleSDKAuthorization(
+      clientID: "xxx-xxx-xxx-xxx",
+      callbackURL: URL(string: "app-scheme://url"))
+   iZettleSDK.shared().start(with: authenticationProvider)
+ } catch {
+   // Inspect error if any, e.g. callback URL not registered in the Xcode project
+   print(error)
+ }
```

`iZettleSDKAuthorizationProvider` is a new public protocol which can be implemented by partners if they want to improve the authorization experience by e.g. managing iZettle tokens themselves and providing them to the SDK directly. Read more in [New Public APIs](#new-public-apis)

##### iOS 9 & iOS 10 support

Partners also need to override AppDelegate `application:openURL:options:` if they need to support iOS 9 and iOS 10.

```swift
func application(
  _ app: UIApplication,
  open url: URL,
  options: [UIApplication.OpenURLOptionsKey : Any] = [:]) -> Bool {
    return iZettleSDK.shared().applicationDidOpen(with: url)
}
```

The `iZettleSDK.shared().applicationDidOpen(with: url)` call will check if the `url` is a valid callback URL, handle it and return `true`. If the `url` is not the callback URL or is invalid the method will return `false`.

### Support for XCFrameworks

New iOS SDK is now distributed as [XCFramework](https://developer.apple.com/videos/play/wwdc2019/416/) bundle which is a new standard way of distributing binary frameworks, released as part of Xcode 11 toolkit. While new format makes manual SDK integration easier, it also enables us to remove the need for stripping unused architectures since that is now natively handled by Xcode. This was previously implemented as part of a "Run Script Phase" and it can be removed after updating to SDK 3.0.

#### Reduced number of frameworks

Previously, the SDK was distributed as a package of 4 different binary frameworks. This has been reduced to 2 binary XCFrameworks:

- `iZettlePayments.xcframework`
- `iZettleSDK.xcframework`

#### Deprecating Carthage support

Carthage doesn't implement support for binary XCFrameworks [Carthage/#2799](https://github.com/Carthage/Carthage/issues/2799) which means that Carthage integration won't work with the new iZettle SDK. We advise all partners to use Manual Integration or Cocoapods instead.

## New Public APIs

### `iZettleSDKAuthorizationProvider` protocol

SDK v3.0.0 implements a new public `iZettleSDKAuthenticationProvider` API to allow integrators to control how authorisation process works. `iZettleSDKAuthenticationProvider` is a new public protocol, and its definition looks like this:

```swift
public typealias iZettleAuthorizationCompletion = (_ tokenData: iZettleSDKOAuthToken?, _ error: Error?) -> Void

/**
 An object conforming to this protocol can be used to authorize the user.
 
 The SDK will call each method when neccesary, asking to provide the required information.
 When a token is provided the SDK will use it and keep it refreshed it until the user is logged out.
 */
@objc public protocol iZettleSDKAuthorizationProvider {
    
    /// Called to request a token.
    ///
    /// This method will only be called once when a valid token is requested, the token will be stored internally for subsequent requests.
    /// - Parameters:
    ///   - completion: Complete with token or error.
    @objc func authorizeAccount(completion: @escaping iZettleAuthorizationCompletion)

    /// Called to request an elevated token.
    ///
    /// Elevated tokens are stored internally but are not refreshed by the SDK.
    /// - Parameters:
    ///   - uuid: The uuid of the account performing the operation which requires elevated token.
    ///   Use this uuid in the verification step.
    ///   - completion: Complete with elevated token or error.
    @objc func verifyAccount(uuid: UUID, completion: @escaping iZettleAuthorizationCompletion)
}
```

Integrators can either chose to implement this protocol and specify how authorisation works, or they can use an `iZettleSDKAuthentication` class that contains the default implementation of this protocol.

### `iZettleSDKAuthorizationProviderError`

The new 

public let iZettleSDKAuthorizationProviderErrorDomain = NSErrorDomain(string: "com.izettle.sdk.authprovider.error")
public enum iZettleSDKAuthorizationProviderError: Int {
    case callbackURLInvalid = -202
    case callbackURLMissing = -203
    case clientIdInvalid = -300
    case presentationNotPossible = -501
}