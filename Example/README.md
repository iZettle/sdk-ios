iOS SDK example app
===

- [iOS SDK example app](#ios-sdk-example-app)
  - [Introduction](#introduction)
    - [Structure](#structure)
  - [Prerequisites](#prerequisites)
  - [Step 1: Configure the example app](#step-1-configure-the-example-app)
  - [Step 2: Initialise the example app](#step-2-initialise-the-example-app)
  - [Step 3: Test the example app](#step-3-test-the-example-app)

## Introduction

The iOS SDK example app is to help you get started with Zettle Payments SDK for iOS.

You can use the example to learn about SDK. For example, SDK structure, input data format, and payment and refund payload.

For information about Zettle Payments SDK for iOS, see [iOS SDK docs on Zettle Developer Portal](https://developer.zettle.com/docs/ios-sdk).

### Structure

Example app is a Xcode project that consists of the following main parts:

 - `AppDelegate` : Main entry point to the app with an example of the ZettleSDK initialisation.
 - `SelectionTableViewController.swift` : View controller responsible for navigating user to different SDK flows.
 - `QRCPaymentViewController.swift` : View controller with an example of triggering PayPal / Venmo QRC flows.
 - `CardPaymentViewController` : View controller with an example of triggering Card payments flows.
 - `CustomAuthorizationProvider.swift` : Service responsible for support of custom authentication (providing access token and refresh tokens to the SDK where needed).

## Prerequisites

- Xcode version 14.1
- Credentials for the app that include a client ID and a redirect  URL (callback URL). If you don't have these, see [create credentials for an SDK app](https://developer.zettle.com/docs/get-started/user-guides/create-app-credentials/create-credentials-sdk-app).

## Step 1: Configure the example app

In the example app Xcode project, fill in  `iZettleSDKSample/AppDelegate.m` with a client ID and a redirect URL to configure the authorisation flow.

```
...
 id<iZettleSDKAuthorizationProvider> authorizationProvider = [[iZettleSDKAuthorization alloc]
                                                              initWithClientID:"<client id from developer portal>"
                                                                   callbackURL:[NSURL URLWithString:@"awesome://login.callback"]
                                                                         error:&error
                                                           enforcedUserAccount:^NSString * _Nullable{
     return [AccountManager shared].enforcedUserAccount;
 }];
 ...
```
> **Note:** The SDK provides default login and custom login. To use custom login for the example app with `iZettleSDKSample/CustomAuthorizationProvider.m`, you need to set up authorisation code grant with PKCE. For more information about custom login, see [Initialise SDK for custom login](https://developer.zettletest.com/docs/ios-sdk/initialization#initialise-sdk-for-custom-login).

## Step 2: Initialise the example app

Initialise the SDK for the default login by including the configuration that you have made in Step 1.

The SDK provides a default login interface for your application users. The default login uses a built-in `iZettleSDKAuthorization` instance that implements the `iZettleSDKAuthorizationProvider` protocol for user authentication and authorisation.

## Step 3: Test the example app

Regardless of where you are located, developer mode lets you quickly check the SDK responses in certain scenarios without a Zettle merchant account and real transactions. For example, taking payments and making refunds for card transactions.

> **Note:** Developer Mode is not meant to be used or accessed in a production environment. This is only meant to be used while integrating the SDK. Make sure that you do not release your app with this option enabled.

Developer mode is disabled by default. Enable it by passing `true` to the `enableDeveloperMode` parameter on `iZettleSDK` start.

```
[[iZettleSDK shared] startWithAuthorizationProvider:authorizationProvider 
                                enableDeveloperMode:true];
```

> **Tip:** You can use developer mode in the example app to test payment and refund responses for card and QRC, see [Try taking payments](https://developer.zettle.com/docs/get-started/user-guides/try-taking-payments).