 [![CocoaPods](https://img.shields.io/cocoapods/v/iZettleSDK.svg)](https://cocoapods.org/pods/iZettleSDK) [![CocoaPods](https://img.shields.io/cocoapods/p/iZettleSDK.svg)](https://cocoapods.org/pods/iZettleSDK)

:warning: **Starting May 9, 2022, all the documentation for iOS SDK is available on [Zettle Developer Portal](https://developer.zettle.com).** 

 **The documentation in this repository is no longer maintained.** 

---

# Zettle SDK for iOS

The Zettle SDK for iOS lets you accept card payments from any iOS app, using a Zettle card reader. It is designed for easy implementation and usage. The SDK places a screen over the host application when triggered. This screen is used for all interaction.

Currently there are these ways to handle payments with the iOS SDK: Card payments, and QRC using PayPal or Venmo. The following table describes the availability in different markets.

| Market | Card Payments |PayPal QRC |Venmo QRC
|:---|:---|:---| :---|
| United States | X | X | X |
| United Kingdom | X | X | - |
| Sweden | X | - | - |
| Brazil | X | - | - |
| Norway | X | - | - |
| Denmark | X | - | - |
| Finland | X | - | - |
| Germany | X | X | - |
| Mexico | X | - | - |
| Netherlands | X | - | - |
| France | X | - | - |
| Spain | X | - | - |
| Italy | X | - | - |

You can only integrate your point of sales (POS) with the Zettle SDK in supported markets. This applies regardless of where you are located.  

> **Note:** To test your integration with the Zettle SDK, you need to order a card reader. This can only be done if you are located in a supported market.

## Main features

- Take card payments with a Zettle card reader.
- Take PayPal QRC payments.
- Take Venmo QRC payments.
- Refund card payments.
- Receive information about a payment.
- Login/logout of Zettle accounts and simple switching between multiple accounts.
- Settings screen. From this a user can handle card readers and access help and support.

## Limitations

- PayPal QRC and Venmo QRC payments are only supported on iOS 13 and higher.

## Contents

- [Requirements](#requirements)
- [Installation](#installation)
- [SDK operations](#sdk-operations)
- [Errors](#errors)

## Requirements

- Xcode 11+
- `ALWAYS_EMBED_SWIFT_STANDARD_LIBRARIES = YES` flag is required if your project doesn't include Swift
- iOS 12+
- Client ID from the Zettle Developer Portal
>**Note:** Support for iOS 10 and 11 was dropped with version 3.4.0 of the iOS SDK.
## Installation

You can install the Zettle SDK in the following ways:

1. [CocoaPods](#cocoapods)
2. [Manual Installation](#manual-installation)

### CocoaPods

[CocoaPods](http://www.cocoapods.org/) is an easy way to install Zettle SDK.

Add the following pod to your `Podfile`:

```ruby
platform :ios, '12.0'

target 'Your App' do
    pod 'iZettleSDK'
end
```

### Manual Installation

Drag the binary frameworks from the `iZettleSDK` folder into your Xcode project:

```
iZettleSDK.xcframework
iZettlePayments.xcframework
```

## Usage

To be able to use the Zettle SDK you need to first set up the following.

>**Note:** An exception will be thrown if these are not set up.

### 1. Set up external accessory protocols in your `Info.plist`

Add/modify the property `Supported external accessory protocols` and add `com.izettle.cardreader-one`.

This is what it should look like in the "source code" view of your `Info.plist` file:

```xml
<key>UISupportedExternalAccessoryProtocols</key>
<array>
    <string>com.izettle.cardreader-one</string>
</array>
```

#### Important

The Zettle Bluetooth card readers are part of the Apple MFi program. In order to release apps supporting accessories that are part of the MFi Program, you have to apply at Apple. Please contact our developer support at [Zettle Developer Portal](https://developer.zettle.com).

### 2. Set up external accessory communication background mode

#### 2.1 Xcode 11

Select the following background modes to enable support for external accessory communication. You can find them under `Signing & Capabilities` in your target.

- `External accessory communication`
- `Uses Bluetooth LE accessory`

#### 2.2 Earlier Xcode versions

In your Xcode project, select the **Capabilities** tab. Go to the **Background modes** section to enable external accessory communication support.

#### 2.3 Edit plist

Edit your **Info.plist** file to have the following information set:

```xml
<key>UIBackgroundModes</key>
<array>
    <string>bluetooth-central</string>
    <string>external-accessory</string>
</array>

<key>NSBluetoothAlwaysUsageDescription</key>
<string>Our app uses bluetooth to find, connect and transfer data with Zettle card reader devices.</string>

<key>NSBluetoothPeripheralUsageDescription</key>
<string>Our app uses bluetooth to find, connect and transfer data with Zettle card reader devices.</string>

<key>CFBundleURLTypes</key>
<array>
    <dict>
        <key>CFBundleTypeRole</key>
        <string>Editor</string>
        <key>CFBundleURLSchemes</key>
        <array>
            <string>"The scheme of your OAuth Redirect URI *"</string>
        </array>
    </dict>
</array>
```

>**Note:** Zettle will ask the user for permission to allow your app access to Blutooth capabilities. Doing so, the texts for `NSLocationWhenInUseUsageDescription` and `NSBluetoothPeripheralUsageDescription` keys are displayed. You may want to update these texts to your requirements.

If you don't remember the scheme of your OAuth Redirect URI, you can verify it on the [Developer Portal](https://developer.zettle.com/).

### 3. Set up CLLocationManager in your `Info.plist`

The merchant must grant your app this permission. If not done, Zettle will prompt the user for permission during the first payment and execute the CLLocationManagers method `requestWhenInUseAuthorization`.

Add the key in your `Info.plist`:

```xml
<key>NSLocationWhenInUseUsageDescription</key>
<string>You need to allow this to be able to accept card payments</string>
```

Zettle won't accept payments without these texts implemented.

### 4. Import SDK framework

Make sure to include the Zettle SDK framework:

**Objective C:**

```objectivec
@import iZettleSDK; 
```

**Swift:**

```swift
import iZettleSDK
```

### 5. Initialize the SDK

Before you execute an operation with the Zettle SDK, it must be initialized, and the user must be authorized. Initialization and authorization are done through the same APIs, using an object that conforms to the `iZettleSDKAuthorizationProvider` protocol. 

This protocol defines a set of methods for authorizing Zettle users inside your application. The Zettle SDK implements this protocol out-of-the-box through an `iZettleSDKAuthorization` object.

User authorization in the SDK is performed through the implementation of OAuth 2.0. A Client ID and a callback URL from your integrating application is required for this.

To get a Client ID, go to the [Zettle Developer Portal](https://developer.zettle.com/login?continue=%2F) and create an account. Then create an iOS SDK developer application. Once you complete that process, you'll be given a Client ID which can be used to initialize the SDK.

```swift
let authenticationProvider = try iZettleSDKAuthorization(
    clientID: "xxx-xxx-xxx-xxx",
    callbackURL: URL(string: "app-scheme://url"))

iZettleSDK.shared().start(with: authenticationProvider)
```


#### Initialize the SDK using token-based authorization

User authorization is most often done through the provided user interface. However, if you have an access token and a refresh token, you will be able to authorize the users through the token-based authorization process. You can use the proof key for code exchange (PKCE) flow to get the required tokens. See see [OAuth PKCE method](https://oauth.net/2/pkce/).

The following example shows how to add support for token-based authorization.


```swift
/// Step 1. Create a class that implements the iZettleSDKAuthorizationProvider protocol.

class YourCustomAuthClass: iZettleSDKAuthorizationProvider {

    ///Step 2. Provide implementation of the `authorizeAccountWithCompletion` method.
    func authorizeAccount(completion: @escaping iZettleAuthorizationCompletion) {
        let token =...
        completion(token, nil)
    }
    
    ///Step 3. Provide implementation of the `verifyAccountWithUuid` method. This is used when triggering refunds.
    func verifyAccount(uuid: UUID, completion: @escaping iZettleAuthorizationCompletion) {
        let token =...
        completion(token, nil)
    }
}
```

See also this custom authorization provider [example](https://github.com/iZettle/sdk-ios/blob/master/Example/iZettleSDKSample/CustomAuthorizationProvider.m).

## SDK Operations

>**Important when calling the methods in the following:** In Objective C, only use the singleton instance returned from `[iZettleSDK shared]`. In Swift, only use the singleton instance returned from `iZettleSDK.shared()`.

The Zettle SDK will handle presentation and dismissal of its views. Operations with UI will accept a UIViewController as an argument. From this the Zettle SDK will be presented. A login screen is displayed if the user has not yet been authenticated with Zettle.

Asynchronous operations have a completion block as an argument. This completion block is called when an operation is considered complete, cancelled or failed. See [iZettleOperationCompletion](#izettleoperationcompletion) for more information. 

* [Card payment](#card-payment)
* [PayPal QRC payment](#paypal-qrc-payment)
* [Presenting settings](#presenting-settings)
* [Enforced user account](#enforced-user-account)
* [Logging out programatically](#logout)


### Card payment

#### Charging

Perform a payment with an amount and a reference:

```objective-c
- (void)chargeAmount:(NSDecimalNumber *)amount
       enableTipping:(BOOL)enableTipping
           reference:(NSString *)reference
presentFromViewController:(UIViewController *)viewController
          completion:(iZettleOperationCompletion)completion;
```

```swift
 open func charge(amount: NSDecimalNumber, 
  currency: String?, 
  enableTipping: Bool, 
  reference: String?, 
  presentFrom viewController: UIViewController, 
  completion: @escaping iZettleSDK.iZettleSDKOperationCompletion)
```

- `amount`: The amount to be charged in the logged in users currency.
- `enableTipping`: Perform payment with tipping flow.
- `currency` _(optional)_: Only used for validation. If the value of this parameter doesn't match the users currency the user will be notified and then logged out. For a complete list of valid currency codes, see [ISO 4217](http://www.xe.com/iso4217.php)
- `reference` _(optional)_: The payment reference. Used to identify a Zettle payment, used when retrieving payment information at a later time or performing a refund. Max length 128.


 **Note on tipping**

It is not enough to pass `enableTipping` to the `charge(amount:)` call for the tipping flow to be displayed. This is because tipping is not supported by all accounts and all card readers. Tipping is only supported with the Zettle Card Reader. The function is introduced market by market.

If the card reader software doesn’t support tipping, users are prompted to skip tipping. Alternatively, users are prompted to update the card reader software.

Total tip amount is presented in `iZettleSDKOperationCompletion` completion with `gratuityAmount` property.

For more information on the tipping flow, see [SDK tipping support documentation](Documentation/SDK_Tipping_Support_Documentation.md).

#### Refunding

Refund an amount from a payment with a given reference.

```objectivec
- (void)refundAmount:(nullable NSDecimalNumber *)amount
ofPaymentWithReference:(NSString *)reference
     refundReference:(nullable NSString *)refundReference
presentFromViewController:(UIViewController *)viewController
          completion:(iZettleSDKOperationCompletion)completion;
```

```swift
open func refund(amount: NSDecimalNumber?, 
  ofPayment reference: String, 
  withRefundReference refundReference: String?, 
  presentFrom viewController: UIViewController, 
  completion: @escaping iZettleSDK.iZettleSDKOperationCompletion)
```

- `amount` _(optional)_: The amount to be refunded from the payment (passing `nil` will refund full amount of original payment).
- `reference`: The reference of the payment that is to be refunded.
- `refundReference` _(optional)_: The reference of the refund. Max length 128.

>**Note:** Demo accounts are accounts that automatically revert performed payments. You cannot use these accounts to perform refunds. Instead, please use a standard production Zettle account to test refund functionality.

#### Retrieving payment info

Query the Zettle SDK for payment information for a payment with a given reference.

```objective-c
- (void)retrievePaymentInfoForReference:(NSString *)reference
              presentFromViewController:(UIViewController *)viewController
                             completion:(iZettleSDKOperationCompletion)completion
```

```swift
open func retrievePaymentInfo(for reference: String,
                                  presentFrom viewController: UIViewController,
                                  completion: @escaping iZettleSDK.iZettleSDKOperationCompletion)
```

#### Processing card payment results

See [iZettleOperationCompletion](Documentation/SDK_card_payment_completion.md) for more details about the completion block.

#### Aborting card payment operations

Aborting an ongoing operation should only be attempted if absolutely necessary. This is because the state of the payment will be unknown to the user after this call.

```objective-c
- (void)abortOperation;
```

```swift
open func abortOperation()
```

### PayPal QRC payment


#### Initializing the SDK for QRC

To start supporting PayPal QRC payments, you need to enable the payment method after [initializing](#5.-initialize-the-sdk) the SDK.

```objectivec
[[iZettleSDK shared] setEnabledAlternativePaymentMethod:@[@(IZSDKAlternativePaymentMethodPayPalQRC)]];
```

```swift
let enabledAPMs = [NSNumber(value: IZSDKAlternativePaymentMethod.payPalQRC.rawValue)]
iZettleSDK.shared().setEnabledAlternativePaymentMethods(enabledAPMs)
```

When using PayPal QRC payments, merchants located in the US can chose to use either PayPal or Venmo when scanning QR codes.

To initialize the SDK to use both PayPal and Venmo QRC types, you need to specify an NSNumber for the `setEnabledAlternativePaymentMethod` function. Passing in "0" enables both PayPal and Venmo QRC, since the Venmo QRC is a subtype of PayPal QRC.


#### Charging


```objectivec
- (void)chargePayPalQRCWithAmount:(NSDecimalNumber *)amount
                        reference:(NSString *)reference
                        appearance:(IZSDKPayPalQRCAppearance)appearance
      presentedFromViewController:(UIViewController *)viewController
                       completion:(IZSDKPayPalQRCCompletion)completion

```

```swift
    func chargePayPalQRC(amount: NSDecimalNumber,
                         reference: String,
                         appearance: IZSDKPayPalQRCAppearance,
                         presentFrom viewController: UIViewController,
                         completion: IZSDKPayPalQRCCompletion)
```

- `amount`: The amount to be charged in the logged-in user's currency.
- `reference`: Non-nullable payment reference. Used to identify a Zettle payment when retrieving payment information at a later time, or performing a refund. Max length 128.


>**Note:** When using PayPal QRC payments, merchants located in the US will have an option to start the payment using PayPal or Venmo UI appearances. This is because consumers can scan the QR code using either the Venmo or PayPal applications. In the payment result, you can extract which payment method was used by the consumer.

See [IZSDKPayPalQRCCompletion documentation](Documentation/SDK_PayPal_QRC_Completion.md) for more details about the completion block.


#### Refunding

Refund an amount from a PayPal QRC payment with a given reference.

```objectivec
- (void)refundPayPalQRCAmount:(nullable NSDecimalNumber *)amount
       ofPaymentWithReference:(NSString *)paymentReference
              refundReference:(NSString *)refundReference
    presentFromViewController:(UIViewController *)viewController
                   completion:(IZSDKPayPalQRCCompletion)completion
```

```swift
    func refundPayPalQRC(amount: NSDecimalNumber?,
                         ofPayment paymentReference: String,
                         withRefundReference refundReference: String,
                         presentFrom viewController: UIViewController,
                         completion: IZSDKPayPalQRCCompletion)
```

- `amount` _(optional)_: The amount to be refunded from the payment (passing `nil` will refund the full amount of the original payment).
- `paymentReference`: The reference of the payment that is to be refunded.
- `refundReference`: The reference of the refund. Max length 128.


#### Retrieving payment info

Query the Zettle SDK for payment information for a PayPal QRC payment with a given reference.

```objectivec
- (void)retrievePayPalQRCPaymentInfoForReference:(NSString *)reference
                       presentFromViewController:(UIViewController *)viewController
                                      completion:(IZSDKPayPalQRCCompletion)completion
```

```swift
    func retrievePayPalQRCPaymentInfo(for reference: String,
                                      presentFrom viewController: UIViewController,
                                      completion: IZSDKPayPalQRCCompletion)
```

### Presenting settings

This is how you present the Zettle settings view. From this, users can switch account, access the FAQ, and see card reader settings.

```objective-c
- (void)presentSettingsFromViewController:(UIViewController *)viewController;
```

```swift
open func presentSettings(from viewController: UIViewController)
```

If you enable the PayPalQRC alternative payment method,  your eligible EU merchants with iOS 13.0+ devices will see the PayPal QRC screen in **Settings**. Eligible US merchants with iOS 13.0+ devices will see the PayPal QRC and Venmo QRC screens.

### Enforced User Account

You can restrict the usage of the SDK to a specific Zettle account. Use the `iZettleSDKAuthorization` object during the SDK initialization, to define the usage.

```swift
var enforcedAccount = { "name@zettle.com" }

let authenticationProvider = try iZettleSDKAuthorization(
    clientID: "xxx-xxx-xxx-xxx",
    callbackURL: URL(string: "app-scheme://url")!,
    enforcedAccount: enforcedAccount)

iZettleSDK.shared().start(with: authenticationProvider)
```

Enforced account will be evaluated for each authenticated operation performed in the SDK.

### Logging out programmatically

Log out the current account.

```objective-c
- (void)logout;
```

```swift
open func logout()
```

## Completion handlers
See the following for more information on completion handlers.
* [Card payment completion handler](Documentation/SDK_card_payment_completion.md)
* [PayPal QRC payment completion handler](Documentation/SDK_PayPal_QRC_Completion.md)


## Errors

Zettle will display any errors that occur during an operation to the end user. The NSError-object returned in the operation completion block is only intended for developers. The object provides more detailed information useful for debugging, diagnostics and logging. You should never present errors returned in this format to the end user.

## Get help
Contact our developer support at [Zettle Developer Portal](https://developer.zettle.com).
