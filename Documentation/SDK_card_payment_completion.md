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