
## IZSDKPayPalQRCCompletion

The completion callback will be called when an operation is completed, canceled, or failed.

### Success payload

Successful completion of the payment will provide `IZSDKPayPalQRCPaymentInfo` with the following details about the transaction.

| Name | Type | Description |
|:---|:---|:---|
| `amount` | `NSDecimalNumber` | Total transaction amount |
| `type` | `IZSDKPayPalQRCType` | Which QRC type was used to perform the payment PayPal or Venmo (USA Only) |
| `referenceNumber` | `NSString` |  Zettle's reference to the payment (not to be confused with the reference provided by you during a charge or refund operation) |
| `paypalTransactionId` | `NSString` | Transaction Identifier that should be displayed on receipts |

The enumeration for the QRC type is in the completion object `IZSDKPayPalQRCType`. All enumerations must be backed up with the integers in Objective C. This means the type you get back from the completion handler is not a standard string of "PayPal" or "Venmo". Therefore you need to implement logic that checks the QRC type and displays whether it was "PayPal" or "Venmo".

### Handling failure 
Failure in completing a payment will generate an NSError. The error message describes the failure, and can contain any of the reasons listed in the following.

| Name  | Description |
|:---|:---|
| IZSDKPayPalQRCNetworkError | Network error
|IZSDKPayPalQRCLocationFailed| Unable to fetch user's location
|IZSDKPayPalQRCFeatureNotEnabled| Payment method is not available for the user
|IZSDKPayPalQRCOnboardingNotCompleted| Payment method activation is in progress
|IZSDKPayPalQRCSellerDataError| Something is wrong with the user's data
|IZSDKPayPalQRCPaymentCancelledByMerchant| Payment was canceled by the seller
|IZSDKPayPalQRCPaymentCancelledByBuyer| Payment was canceled by the buyer
|IZSDKPayPalQRCPaymentTimeout| Payment session has timed out
|IZSDKPayPalQRCNotAuthorized| User is not authorized for this action
|IZSDKPayPalQRCNotFound| No payment could be found for this reference
|IZSDKPayPalQRCRetrievalCancelled| Payment info retrieval has been canceled by the seller
|IZSDKPayPalQRCRefundAmountTooHigh| Requested amount couldn't be refunded for the payment
|IZSDKPayPalQRCRefundInsufficientFunds| There are not enough funds to perform refund in the seller's account
|IZSDKPayPalQRCRefundFailed| Payment is not refundable
|IZSDKPayPalQRCRefundCancelled| Payment refund has been canceled by the seller
|IZSDKPayPalQRCInvalidAmount| Provided amount is invalid
|IZSDKPayPalQRCAmountBelowMinimum| Provided amount is below the minimum amount
|IZSDKPayPalQRCAmountAboveMaximum| Provided amount is above the maximum amount
|IZSDKPayPalQRCTechnicalError| Unexpected technical error