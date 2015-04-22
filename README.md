# iZettle SDK Documentation

## Installation guide


### 1. Requirements
* iOS 7.1 or later
* XCode 6 (iOS 8 SDK)
* An iZettle API Key (please visit [http://developer.izettle.com](http://developer.izettle.com/) in order to obtain one)

### 2. Include the following framework and bundles in your project

    iZettleSDK.framework
    iZettleShared.bundle
    iZettleStorePurchase.bundle

Make sure that the bundles are included in the “Copy Bundle Resources” build phase.

### 3. Make sure you link with the following frameworks and libraries

    libiZettleSDK.a
    libz.dylib
    libc++.dylib
    SystemConfiguration.framework
    CoreLocation.framework
    ExternalAccessory.framework
    AudioToolbox.framework
    AVFoundation.framework
    MediaPlayer.framework
    QuartzCore.framework
    Accelerate.framework
    MessageUI.framework

### 4. Modify your targets "Other Linker Flags" and add

    -ObjC

### 5. Setup external accessory protocols in info.plist

Add/modify the property "Supported external accessory protocols" and add *com.miura.shuttle.izettle*

This is what it should look like in the "source code" view of your info.plist:

    <key>UISupportedExternalAccessoryProtocols</key>
    <array>
        <string>com.miura.shuttle.izettle</string>
    </array>
    
**Important**

The iZettle bluetooth card reader is part of the Apple MFi program. In order to release apps supporting accessories that are part of the MFi Program, you have to apply at Apple. Please contact us at [sdk@izettle.com](sdk@izettle.com) and we will help you with this process.

### 6. Setup CLLocationManager texts in info.plist

iZettle will prompt the user for permission during the first payment if the merchant haven't already granted your app this permission. On iOS8, iZettle will execute CLLocationManagers method `requestWhenInUseAuthorization`.

Add the keys:

- **NSLocationUsageDescription** (iOS7)
- **NSLocationWhenInUseUsageDescription** (iOS8)

Suggested value for the above keys is `"You need to allow this to be able to accept card payments."`

iZettle won't accept payments without these texts implemented.

### 7. Include the framework headers and start the SDK

Make sure to include the iZettle SDK header:

    #import <iZettleSDK/iZettleSDK.h> 

Before you execute any operations in iZettle SDK, you have to start the SDK with your API key. This is typically done in your AppDelegates method `application:didFinishLaunchingWithOptions:`.

    - (void)startWithAPIKey:(NSString *)apiKey;
    
Example:

	- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    	[[iZettleSDK shared] startWithAPIKey:@"API_KEY"];
    	return YES;
	}

## Operations

**Important:** Only use the singleton instance returned from `[iZettleSDK shared]` when calling the methods below.

Asynchronous operations have a completion block as an argument, the completion block is called when an operation is considered complete, cancelled or failed. See **iZettleOperationCompletion** for more information.

iZettle SDK will handle presentation and dismissal of its views. Operations with UI will accept a UIViewController  as an argument from which iZettle SDK will be presented.

If the user isn't yet authenticated with iZettle when an operation is presented, a login screen will automatically be displayed.

### Charge

Perform a payment with an amount and a reference.

	- (void)chargeAmount:(NSDecimalNumber *)amount
                currency:(NSString *)currency
        	   reference:(NSString *)reference
	presentFromViewController:(UIViewController *)viewController
          	  completion:(iZettleOperationCompletion)completion;

- **amount**: The amount to be charged in the logged in users currency.
- **currency** _(optional)_: Only used for validation. If the value of this parameter doesn't match the users currency the user will be notified and then logged out. For a complete list of valid currency codes, see [ISO 4217](http://www.xe.com/iso4217.php)
- **reference** _(optional)_: The payment reference. Used to identify an iZettle payment, used when retrieving payment information at a later time or performing a refund. Max length 128.

### Refund

Refund a payment with a given reference.

	- (void)refundPaymentWithReference:(NSString *)reference
                   	   refundReference:(NSString *)refundReference
         	 presentFromViewController:(UIViewController *)viewController
                      	    completion:(iZettleOperationCompletion)completion;
	
- **reference**: The reference of the payment that is to be refunded.
- **refundReference** _(optional)_: The reference of the refund. Max length 128.

### Retrieve payment info

Query iZettle for payment information of a payment with a given reference.

	- (void)retrievePaymentInfoForReference:(NSString *)reference
                             	 completion:(iZettleOperationCompletion)completion;

### Present settings

Present iZettle settings view. The user can switch account, access the iZettle FAQ, view card reader settings etc.

	- (void)presentSettingsFromViewController:(UIViewController *)viewController;
	
### Abort operation

Attempt aborting the ongoing operation. Only use this if absolutely necessary. The state of the payment will be unknown to the user after this call.

	- (void)abortOperation;

## iZettleOperationCompletion

### iZettlePaymentInfo

Object that contains information about a payment and the card used.

- **referenceNumber** - iZettles reference to the payment (not to be confused with the reference provided by you during a charge or refund operation)
- **entryMode** - EMV, MAGSTRIPE or MANUAL_ENTRY
- **obfuscatedPan** - e.g. _"\*\*\*\* \*\*\*\* \*\*\*\* 1111"_
- **panHash** - a hash of the pan
- **cardBrand**
- **AID***
- **TSI***
- **TVR***
- **applicationName***
- **numberOfInstallments**
- **installmentAmount**

\* These fields are only for EMV (non refund) payments

#### Example of a card reader chip payment:

	entryMode = EMV
	obfuscatedPan = "**** **** **** 0640"
	panHash = 0092C7D95900033B84CE08B43F7E973485FB7081
	cardBrand = MASTERCARD
    AID = A0000000041010
    TSI = 4000
    TVR = 8000000000
    applicationName = MasterCard
    
#### Example of a card reader swipe payment:

    entryMode = MAGSTRIPE
    obfuscatedPan = "**** **** **** 2481"
    panHash = 99426D012C6740D9AEC8E26580E8640A196E3C27
    cardBrand = MASTERCARD

#### Example of a manual entry payment:

	entryMode = MANUAL_ENTRY
    obfuscatedPan = "**** **** **** 1111"
    panHash = 3E00BFA91E68894D5B6911A93C0F8C185708877B
    cardBrand = VISA
    
### Errors

iZettle will display any errors that occur during an operation to the user, the NSError-object returned in the operation completion block is only intended to be used by developers for debugging, diagnostics and logging to be able to better communicate errors to iZettle. You should never present the returned errors to the end user.

