# Zettle SDK support for tipping
The purpose of this document is to provide an overview of how to receive tips when taking card payments using the SDK from Zettle.

### Description of tipping flow in the SDK
The usage of tipping is optional. For each call the requestor can specify if tipping should be part of the payment or not. If tipping is enabled, the payment will return both the total amount and the tipping amount.
Example​: Merchant initiates a payment of 150 and tipping is enabled. The card holder decides to give an additional 20 as a tip. The total amount returned from the call would be 170 and the tipping amount would contain 20.

### Different tipping styles in the card reader
The process to enter tips in the card reader may vary between markets due to to differences in tipping behaviour. From an SDK perspective there is no difference however. The market specific logic is handled by the SDK and the card reader.

### Prerequisites
Please note that the following prerequisites are required to initiate tipping,

- Tipping is only available on the Zettle reader
- Usage of SDK version ​`1.7.1`
- The card reader needs to contain the latest software versions.
- Tipping needs to be enabled for the market connected to the Zettle account used by the merchant. Please refer to list of supported markets below.

### Supported markets for tipping
Tipping will be made available on a market by market basis. The following markets are supported at the moment:

- United States
- Sweden
- Norway
- Denmark
- Finland
- United Kingdom
- The Netherlands
- Germany

### Additional material

- Zettle SDK FAQ Tipping
- Instruction of how to update Zettle reader software
- Description of user interaction on Zettle reader when receiving tips

## Zettle SDK FAQ tipping

### How does the tipping feature work in the Zettle SDK and Zettle Reader?

Zettle's tipping function allows customers to add an extra amount to the total sum of their bill (market specific versions: entering total sum or adding an extra amount), and they can do so straight into your card reader. This function only works with a Zettle Reader.

### How do I activate the tipping function within the SDK?
Tipping is optional and is enabled per call to the charge-function.
Passing enableTipping to the `charge(amount:)` call does not guarantee that tipping flow will be displayed. This is because tipping is not supported by all accounts and all card readers.


### Why are the different flows in the card reader to collect tips?
User research showed that the methods to give tips differ between countries. In the UK users want to be prompted with a question before entering the tip amount. As a contrast in Norway and Sweden, users prefer to enter the total amount including tip directly.

### Are there any prerequisites for using tipping?
See section [prerequisites](#prerequisites).

### Why are the different flows in the card reader to collect tips?
User research showed that the methods to give tips differ between countries. In the UK users want to be prompted with a question before entering the tip amount. As a contrast in Norway and Sweden, users prefer to enter the total amount including tip directly.

 ![alt text][reader_front_total] | ![alt text][reader_front_extra] 
 :------: | :------: 
  *Total Amount* | *Extra Amount* 

### Are the tipping styles configurable?
The tipping style is pre-defined per market and is not configurable.

| Market | Tipping style |
| ------ | ------ |
| United States | Extra Amount |
| Sweden | Total Amount |
| Norway | Total Amount |
| Denmark | Extra Amount |
| Finland | Total Amount |
| United Kingdom | Extra Amount |
| The Netherlands | Total Amount |
| Germany | Total Amount |

### Is there a MAX level for tip?
To prevent accidental or invalid amounts (for example if the customer enters their PIN code instead of a tip amount), the maximum tip level is set to 50%. If the customer enters more than 50%, the card reader will show a “too high amount” warning message.

### Is there a MIN level for tip?
In markets where the tipping style is `Total amount`, there card holder is required to enter the amount to be charged including tips. If the user enters an amount that is less than the amount entered by the merchant, the card reader will show a “too low amount” warning message.

### Is there a need to update the card reader software to use tipping?
Yes, tipping requires a minimum version of the card reader software. It’s highly recommended that merchants upgrade the card reader software prior to accepting payments with tips. The update will take a few minutes to be completed.

The SDK will verify that the correct software is installed on the Zettle card reader when requesting tips. If the card reader software doesn’t support tipping, a message will be displayed asking the merchant to update the card reader software.

![alt text][update_software2]

---
#### ⚠️ Important ⚠️
- Make sure that the card reader and your smartphone or tablet are charged before you update the software.
- Keep the smartphone or tablet close to the card reader during the update.
---

### What happens if a tipping call is made using a Zettle account in a market that doesn’t support tipping?
​The payment function will work as before, eg not initiating the tipping flow in the card reader.

### What are the plans to launch tipping for other Zettle markets?
Tipping is planned be introduced in more markets. Information about the availability will be announced on Github and via email.

## How to update Zettle card reader software
This document describes the process to update the Zettle reader software.

![alt text][reader0]

Card reader software updates are initiated from the settings window in the SDK. Your app needs to call the `presentSettings` function in the SDK to launch the settings window.The user needs to click ‘Card readers’ pane.

![alt text][update_software0]

When there is a software update available, a button labeled ‘Update card reader’ is shown. Clicking the button will initiate the software update on the card reader. This will take a few minutes.

![alt text][update_software1]

---
#### ⚠️ Important ⚠️
- Make sure that the card reader and your smartphone or tablet are charged before you update the software.
- Keep the smartphone or tablet close to the card reader during the update.
---

During the update the follow screen is shown.

![alt text][update_software3]

[reader_front_total]: ./images/iZ_Reader_Front_blue_TOTAL-AMOUNT_flow.png "Total Amount"
[reader_front_extra]: ./images/iZ_Reader_Front_blue_EXTRA-AMOUNT_flow.png "Extra Amount"
[reader0]: ./images/iZ_Reader.png "Reader"
[update_software0]: ./images/iZ_Payment_UpdateReader_0.png "Update software 0"
[update_software1]: ./images/iZ_Payment_UpdateReader_1.png "Update software 1"
[update_software2]: ./images/iZ_Payment_UpdateReader_2.png "Update software 2"
[update_software3]: ./images/iZ_Payment_UpdateReader_3.png "Update software 3"