 [![CocoaPods](https://img.shields.io/cocoapods/v/iZettleSDK.svg)](https://cocoapods.org/pods/iZettleSDK) [![CocoaPods](https://img.shields.io/cocoapods/p/iZettleSDK.svg)](https://cocoapods.org/pods/iZettleSDK) [![Carthage compatible](https://img.shields.io/badge/Carthage-compatible-4BC51D.svg?style=flat)](https://github.com/Carthage/Carthage)

# iZettle SDK for iOS

The iZettle SDK makes it possible to accept card payments with an iZettle card reader from any iOS app.
When triggered, it will display a screen over the host application where all interaction takes place. It 
is designed to be easy to implement and use. 

## Main features
- Take card payments with an iZettle card reader.
- Refund card payments.
- Receive information about a payment.
- Login/logout of iZettle accounts and simple switching between multiple accounts.
- Settings screen where the user can handle card readers and access help and support.

#### Limitations:
- The SDK will only work on markets where iZettle is operating, please visit [iZettle.com](https://www.izettle.com) for more information.
- It does not currently support other payment methods than cards.

## Contents:

* [Requirements](#requirements)
* [Installation](#installation)
* [SDK Operations](#sdk-operations)
* [Errors](#errors)

## Requirements
* iOS 8 or later
* Xcode 7 (iOS 9 SDK)
* An iZettle SDK Key. Visit [iZettle Developer Page](https://www.izettle.com/gb/developer) in order to obtain one. **Note: SDK keys only work for apps using the same bundle identifier as the one they key were issued for.**

## Installation

You can install iZettle SDK in several ways:

1. [CocoaPods](#cocoapods)
2. [Carthage](#carthage)
3. [Manual Installation](#manual-installation)

### CocoaPods

[CocoaPods](http://www.cocoapods.org/) is an easy way to install iZettleSDK.

1. Add following pod to your `Podfile`:

```ruby
platform :ios, '8.0'

target 'Your App' do
    pod 'iZettleSDK'
end
```

2. Create a new “Run Script Phase” in your app’s target’s “Build Phases” and paste the following snippet in the script text field:

```bash
bash "${BUILT_PRODUCTS_DIR}/${FRAMEWORKS_FOLDER_PATH}/iZettleSDK.framework/strip-frameworks.sh"
```

This step is required to work around an [App Store submission](http://www.openradar.me/radar?id=6409498411401216) bug when archiving universal binaries.

### Carthage

Since iZettle SDK is distributed as a binary, you need to use custom `binary` rule in your `Cartfile`.

1. Add following to your `Cartfile`:

```
binary "https://raw.githubusercontent.com/iZettle/sdk-ios/master/Carthage/iZettleSDK.json" >= 1.6.1
```

2. Fetch frameworks by running:

```bash
$ carthage update iZettleSDK
```

### Manual Installation

1. Add the iZettle frameworks to Embedded Frameworks for your target:

```
iZettleSDK.framework
iZettlePayments.framework
iZettleShared.framework
```

2. Make sure you link with the following frameworks and libraries:

```
iZettleSDK.framework
iZettlePayments.framework
iZettleShared.framework
Accelerate.framework
AudioToolbox.framework
AVFoundation.framework
CoreData.framework 
CoreLocation.framework
ExternalAccessory.framework
libc++.tdb
libz.tdb
MediaPlayer.framework
MessageUI.framework
SystemConfiguration.framework
QuartzCore.framework
```

3. Create a new “Run Script Phase” in your app’s target’s “Build Phases” and paste the following snippet in the script text field:

```bash
bash "${BUILT_PRODUCTS_DIR}/${FRAMEWORKS_FOLDER_PATH}/iZettleSDK.framework/strip-frameworks.sh"
```

This step is required to work around an [App Store submission](http://www.openradar.me/radar?id=6409498411401216) bug when archiving universal binaries.

## Usage

To be able to use iZettle SDK you need to setup several things first

### 1. Setup external accessory protocols in your `Info.plist`

Add/modify the property "Supported external accessory protocols" and add *com.miura.shuttle.izettle* and *com.izettle.cardreader-one*

This is what it should look like in the "source code" view of your info.plist:

```plist
<key>UISupportedExternalAccessoryProtocols</key>
<array>
    <string>com.izettle.cardreader-one</string>
    <string>com.miura.shuttle.izettle</string>
</array>
```

**Important**

The iZettle bluetooth card readers are part of the Apple MFi program. In order to release apps supporting accessories that are part of the MFi Program, you have to apply at Apple. Please contact us at  [sdk@izettle.com](mailto:sdk@izettle.com) and we will help you with this process.

### 2. Setup CLLocationManager keys in your `Info.plist`

iZettle will prompt the user for permission during the first payment if the merchant haven't already 
granted your app this permission. On iOS8, iZettle will execute CLLocationManagers method 
`requestWhenInUseAuthorization`.

Add the keys:

- `NSLocationUsageDescription` (iOS7)
- `NSLocationWhenInUseUsageDescription` (iOS8)

Suggested value for the keys above is `"You need to allow this to be able to accept card payments."`

iZettle won't accept payments without these texts implemented.

### 3. Import SDK framework

Make sure to include the iZettle SDK framework:

**Objective C:**
```objective-c
@import iZettleSDK; 
```

**Swift:**
```swift
import iZettleSDK
```

### 4. Setup your API key

Before you execute any operations in iZettle SDK, you have to start the SDK with your API key. This is 
typically done in your AppDelegates method `application:didFinishLaunchingWithOptions:`.

**Objective C:**
```objective-c
- (void)startWithAPIKey:(NSString *)apiKey;
```

**Swift:**
```swift
open func start(withAPIKey apiKey: String)
```

For example:

**Objective C:**
```objective-c
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    [[iZettleSDK shared] startWithAPIKey:@"API_KEY"];
    return YES;
}
```

**Swift:**
```swift
func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
    iZettleSDK.shared().start(withAPIKey: "API_KEY")
    return true
}
```

## SDK Operations

**Important:** Only use the singleton instance returned from `[iZettleSDK shared]` (in Objective C) or `iZettleSDK.shared()` (in Swift) when calling the methods below.

Asynchronous operations have a completion block as an argument, the completion block is called when an 
operation is considered complete, cancelled or failed. See [iZettleOperationCompletion](#izettleoperationcompletion) for more information.

iZettle SDK will handle presentation and dismissal of its views. Operations with UI will accept a UIViewController as an argument from which iZettle SDK will be presented.

If the user isn't yet authenticated with iZettle when an operation is presented, a login screen will automatically be displayed.

* [Enforced User Account](#enforced-user-account)
* [Charging](#charging)
* [Refunding](#refunding)
* [Retrieving payment info](#retrieve-payment-info)
* [Aborting operation](#aborting-operation)

### Enforced User Account

- `enforcedUserAccount` _(optional)_: If set, operations will be restricted to only work for the specified iZettle username.

By setting the shared instance property `enforcedUserAccount` to an iZettle username, subsequent operations will be restricted to only be performed on that account. If the set enforced user account was not previosuly logged in, an iZettle login prompt will be presented with a readonly email field prefilled with the enforced user account. If the enforced user account was already logged in (even though another account has been used in between), the account will be switched to use the enforced user account account instead. 

If `enforcedUserAccount` is set to nil, any iZettle account can be used, and the email field will be editable.

Enforced user account can be changed between operations to allow switching between different users for different operations. This is useful for integrators supporting multiple accounts. 

Preferably integrating apps will provide a settings page where the user can enter their iZettle account (used to set the enforced user account).

### Charging

Perform a payment with an amount and a reference:

```objective-c
- (void)chargeAmount:(NSDecimalNumber *)amount
            currency:(NSString *)currency
           reference:(NSString *)reference
presentFromViewController:(UIViewController *)viewController
          completion:(iZettleOperationCompletion)completion;
```

```swift
open func chargeAmount(_ amount: NSDecimalNumber, 
                       currency: String?, 
                       reference: String?, 
                       presentFrom viewController: UIViewController, 
                       completion: @escaping iZettleSDK.iZettleSDKOperationCompletion)
```

- `amount`: The amount to be charged in the logged in users currency.
- `currency` _(optional)_: Only used for validation. If the value of this parameter doesn't match the users currency the user will be notified and then logged out. For a complete list of valid currency codes, see [ISO 4217](http://www.xe.com/iso4217.php)
- `reference` _(optional)_: The payment reference. Used to identify an iZettle payment, used when retrieving payment information at a later time or performing a refund. Max length 128.

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
open func refundAmount(_ amount: NSDecimalNumber?, 
                       ofPaymentWithReference reference: String, 
                       refundReference: String?, 
                       presentFrom viewController: UIViewController, 
                       completion: @escaping iZettleSDK.iZettleSDKOperationCompletion)
```

- `amount` _(optional)_: The amount to be refunded from the payment (passing `nil` will refund full amount of original payment)
- `reference`: The reference of the payment that is to be refunded.
- `refundReference` _(optional)_: The reference of the refund. Max length 128.

**Note:** Demo accounts (accounts that automatically revert performed payments) cannot be used to perform refunds. To test refund functionality please use a standard production iZettle account.

### Retrieving payment info

Query iZettle for payment information of a payment with a given reference.

```objective-c
- (void)retrievePaymentInfoForReference:(NSString *)reference
                             completion:(iZettleOperationCompletion)completion;
```

```swift
open func retrievePaymentInfo(forReference reference: String, 
                              presentFrom viewController: UIViewController, 
                              completion: @escaping iZettleSDK.iZettleSDKOperationCompletion)
```

### Presenting settings

Present iZettle settings view. The user can switch account, access the iZettle FAQ, view card reader settings etc.

```objective-c
- (void)presentSettingsFromViewController:(UIViewController *)viewController;
```

```swift
open func presentSettings(from viewController: UIViewController)
```

### Abort operation

Attempt aborting the ongoing operation. Only use this if absolutely necessary. The state of the payment will 
be unknown to the user after this call.

```objective-c
- (void)abortOperation;
```

```swift
open func abortOperation()
```

## iZettleOperationCompletion

### iZettlePaymentInfo

Object that contains information about a payment and the card used.

- `referenceNumber` - iZettles reference to the payment (not to be confused with the reference provided by you during a charge or refund operation)
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

iZettle will display any errors that occur during an operation to the user, the NSError-object returned in the operation completion block is only intended to be used by developers for debugging, diagnostics and logging to be able to better communicate errors to iZettle. You should never present the returned errors to the end user.

