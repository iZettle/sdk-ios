# iZettle SDK v2.0 migration guide

iZettle SDK 2.0 is latest major release containing support for iZettle Reader 2. This guide is provided in order to ease the transition of existing applications using iZettle SDK 1.0+ to the latest release.

## Linking with new framework

iZettle SDK v2.0 introduces a new `iZettleTransport` framework. This framework needs to be linked along current frameworks (`iZettleSDK`, `iZettleShared`, and `iZettlePayments`) in order to work. More info on installation can be found [here](https://github.com/iZettle/sdk-ios#installation).

## Using BLE technology in background modes

The new iZettle Reader 2 uses BLE technology to communicate with the SDK. To make sure that apps using SDK can communicate and work with the new readers in background, you need to enable **Use BLE accessories** in Background Modes in Xcode capabilities. 

You can also do this step manually, and make the change directly in your apps `Info.plist` file. The `UIBackgroundModes` values should look like this:

```
<key>UIBackgroundModes</key>
	<array>
		<string>bluetooth-central</string>
		<string>external-accessory</string>
	</array>
```

