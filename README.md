 [![CocoaPods](https://img.shields.io/cocoapods/v/iZettleSDK.svg)](https://cocoapods.org/pods/iZettleSDK) [![CocoaPods](https://img.shields.io/cocoapods/p/iZettleSDK.svg)](https://cocoapods.org/pods/iZettleSDK)

# Zettle SDK for iOS

The Zettle SDK for iOS lets you accept card payments from any iOS app, using a Zettle card reader. It is designed for easy implementation and usage. The SDK places a screen over the host application when triggered. This screen is used for all interaction.

Card payments with Zettle are currently supported in the following markets:

-   United States
-   United Kingdom
-   Sweden
-   Brazil
-   Norway
-   Denmark
-   Finland
-   Germany
-   Mexico
-   Netherlands
-   France
-   Spain
-   Italy

You can only integrate your point of sales (POS) with the Zettle SDK in supported markets. This applies regardless of where you are located. 

> **Note:** To test your integration with the Zettle SDK, you need to order a card reader. This can only be done if you are located in a supported market.

## Main features

- Take card payments with a Zettle card reader.
- Refund card payments.
- Receive information about a payment.
- Login/logout of Zettle accounts and simple switching between multiple accounts.
- Settings screen. From this a user can handle card readers and access help and support.

## Limitations

- The Zettle iOS SDK does currently not support other payment methods than cards.

## Contents

- [Requirements](#requirements)
- [Installation](#installation)
- [SDK Operations](#sdk-operations)
- [Errors](#errors)

## Requirements

- Xcode 11+
- `ALWAYS_EMBED_SWIFT_STANDARD_LIBRARIES = YES` flag is required if your project doesn't include swift
- iOS 10+
- Client ID from the Zettle Developer Portal

## Installation

You can install Zettle SDK in several ways:

1. [CocoaPods](#cocoapods)
2. [Manual Installation](#manual-installation)

### CocoaPods

[CocoaPods](http://www.cocoapods.org/) is an easy way to install Zettle SDK.

1. Add following pod to your `Podfile`:

```ruby
platform :ios, '10.0'

target 'Your App' do
    pod 'iZettleSDK'
end
```

### Manual Installation

1. Drag the binary frameworks from the `iZettleSDK` folder into your Xcode project:

```
iZettleSDK.xcframework
iZettlePayments.xcframework
```

## Usage

To be able to use Zettle SDK you are **required** to setup several things first

```
⚠️ An exception will be thrown if these are not selected
```

### 1. Setup external accessory protocols in your `Info.plist`

Add/modify the property `Supported external accessory protocols` and add `com.izettle.cardreader-one`.

This is what it should look like in the "source code" view of your `Info.plist` file:

```xml
<key>UISupportedExternalAccessoryProtocols</key>
<array>
    <string>com.izettle.cardreader-one</string>
</array>
```

#### Important

The Zettle bluetooth card readers are part of the Apple MFi program. In order to release apps supporting accessories that are part of the MFi Program, you have to apply at Apple. Please contact our [Integrations team](mailto:sdk@zettle.com) and we will help you with this process.

### 2. Setup external accessory communication background mode

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

**Note:** Zettle will ask the user for permission to allow your app access to Blutooth capabilities. Doing so, the texts for `NSLocationWhenInUseUsageDescription` and `NSBluetoothPeripheralUsageDescription` keys are displayed. You may want to update these texts to your requirements.

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

Before you execute an operation with the Zettle SDK, it must be initialized. This is done using an object that conforms to the `iZettleSDKAuthorizationProvider` protocol. This protocol defines a set of methods for authorizing Zettle users inside your application. The Zettle SDK implements this protocol out-of-the-box through an `iZettleSDKAuthorization` object.

User authorization in the SDK is performed through the implementation of OAuth 2.0. A Client ID and a callback URL from your integrating application is required for this. 

To get a Client ID, go to the [Zettle Developer Portal](https://developer.zettle.com/login?continue=%2F) and create an account. Then create an iOS SDK developer application. Once you complete that process, you'll be given a Client ID which can be used to initialize the SDK.

```swift
let authenticationProvider = try iZettleSDKAuthorization(
    clientID: "xxx-xxx-xxx-xxx",
    callbackURL: URL(string: "app-scheme://url"))

iZettleSDK.shared().start(with: authenticationProvider)
```

If your application supports iOS 10 and iOS 11, then override the AppDelegate `application:openURL:options:` method:

```swift
func application(
  _ app: UIApplication,
  open url: URL,
  options: [UIApplication.OpenURLOptionsKey : Any] = [:]) -> Bool {
    return iZettleSDK.shared().applicationDidOpen(with: url)
}
```

The `ZettleSDK.shared().applicationDidOpen(with: url)` call will check `url`. If `url` is a valid callback URL, it will return `true`. If the `url` is not the callback URL or is invalid, the method will return `false`.

## SDK Operations

⚠️ **Important when calling the methods in the following:** In Objective C, only use the singleton instance returned from `[iZettleSDK shared]`. In Swift, only use the singleton instance returned from `iZettleSDK.shared()`.

The Zettle SDK will handle presentation and dismissal of its views. Operations with UI will accept a UIViewController as an argument. From this the Zettle SDK will be presented. A login screen is displayed if the user has not yet been authenticated with Zettle.

Asynchronous operations have a completion block as an argument. This completion block is called when an operation is considered complete, cancelled or failed. See [iZettleOperationCompletion](#izettleoperationcompletion) for more information.

* [Charging](#charging)
* [Refunding](#refunding)
* [Retrieving payment info](#retrieving-payment-info)
* [Aborting operations](#aborting-operations)
* [Enforced User Account](#enforced-user-account)

### Charging

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
- `currency` _(optional)_: Only used for validation. If the value of this parameter doesn't match the user´s currency, the user is notified and then logged out. For a complete list of valid currency codes, see [ISO 4217](http://www.xe.com/iso4217.php).
- `reference` _(optional)_: The reference for identifying a Zettle payment. Used when retrieving payment information at a later time, or when performing a refund. Max length 128.


#### Note on tipping

It is not enough to pass `enableTipping` to the `charge(amount:)` call for the tipping flow to be displayed. This is because tipping is not supported by all accounts and all card readers. Tipping is only supported with the Zettle Card Reader. The function is introduced market by market. If the card reader software doesn’t support tipping, users are prompted to skip tipping. Alternatively, users are prompted to update the card reader software.

Total tip amount is presented in `iZettleSDKOperationCompletion` completion with `gratuityAmount` property.

For more information on the tipping flow, see [SDK tipping support documentation](Documentation/SDK_Tipping_Support_Documentation.md).

### Refunding

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

- `amount` _(optional)_: The amount to be refunded from the payment. Passing `nil` will refund the full amount of the original payment.
- `reference`: The reference of the payment that is to be refunded.
- `refundReference` _(optional)_: The reference of the refund. Max length 128.

**Note:** Demo accounts are accounts that automatically revert performed payments. You cannot use these accounts to perform refunds. Instead, please use a standard production Zettle account to test refund functionality.

### Retrieving payment info

Query Zettle for payment information of a payment with a given reference.

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

### Presenting settings

This is how you present the Zettle settings view. From this, users can switch account, access the FAQ, and see card reader settings.

```objective-c
- (void)presentSettingsFromViewController:(UIViewController *)viewController;
```

```swift
open func presentSettings(from viewController: UIViewController)
```

### Aborting operations

Aborting an ongoing operation should only be attempted if absolutely necessary. This is because the state of the payment will be unknown to the user after this call.

```objective-c
- (void)abortOperation;
```

```swift
open func abortOperation()
```

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

Log out current account.

```objective-c
- (void)logout;
```

```swift
open func logout()
```

## iZettleOperationCompletion

### iZettlePaymentInfo

Object that contains information about a payment and the card used.

- `amount` - Total transaction amount (also includes tip amount if applicable)
- `gratuityAmount` - Contains total tip amount if tipping is performed
- `referenceNumber` - Zettles reference to the payment (not to be confused with the reference provided by you during a charge or refund operation)
- `entryMode` - EMV, CONTACTLESS_EMV, MAGSTRIPE_CONTACTLESS, MAGSTRIPE etc. More entry modes might be added independent of SDK version
- `obfuscatedPan` - e.g. _"\*\*\*\* \*\*\*\* \*\*\*\* 1111"_
- `panHash` - a hash of the pan
- `cardBrand`
- `authorizationCode`
- `AID`
- `TSI`
- `TVR`
- `applicationName`
- `numberOfInstallments`
- `installmentAmount`

\* These fields are only available for some entry modes. Don't rely on them being present.

#### Example of a card reader chip payment:

```
entryMode = EMV
obfuscatedPan = "**** **** **** 0640"
panHash = 0092C7D95900033B84CE08B43F7E973485FB7081
cardBrand = MASTERCARD
authorizationCode = 007602
AID = A0000000041010
TSI = 4000
TVR = 8000000000
applicationName = MasterCard
```

#### Example of a card reader contactless payment:

```
entryMode = CONTACTLESS_EMV
obfuscatedPan = "**** **** **** 0640"
panHash = 0092C7D95900033B84CE08B43F7E973485FB7081
cardBrand = MASTERCARD
authorizationCode = 007602
AID = A0000000041010
TVR = 8000000000
applicationName = MasterCard
```

#### Example of a card reader swipe payment:

```
entryMode = MAGSTRIPE
obfuscatedPan = "**** **** **** 2481"
panHash = 99426D012C6740D9AEC8E26580E8640A196E3C27
cardBrand = MASTERCARD
authorizationCode = 004601
```

## Errors

Zettle will display any errors that occur during an operation to the end user. The NSError-object returned in the operation completion block is only intended for developers. The object provides more detailed information useful for debugging, diagnostics and logging. You should never present errors returned in this format to the end user.

## Get help
Contact our [Integrations team](mailto:sdk@zettle.com) for more information.
