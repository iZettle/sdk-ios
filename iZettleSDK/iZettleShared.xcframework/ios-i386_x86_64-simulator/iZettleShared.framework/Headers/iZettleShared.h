//
//  Shared.h
//  Shared
//
//  Created by Måns Bernhardt on 2015-09-15.
//  Copyright © 2015 iZettle. All rights reserved.
//

@import UIKit;

//! Project version number for Shared.
FOUNDATION_EXPORT double iZettleSharedVersionNumber;

//! Project version string for Shared.
FOUNDATION_EXPORT const unsigned char iZettleSharedVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <Shared/PublicHeader.h>

#import "NSBundle+iZettleShared.h"

#import "Log.h"
#import "IZCurrency.h"
#import "Dingbatz.h"
#import "LocalizationExtensions.h"
#import "LocalizationManager.h"
#import "LocalizedViewController.h"
#import "NSData+Base64.h"
#import "NSDictionary+EncodedQueryString.h"
#import "NSDictionary+Utilities.h"
#import "NSNumberFormatter+Utilities.h"
#import "NSString+URLEncoding.h"
#import "NSString+Utilities.h"
#import "NSURL+Utilities.h"
#import "NumericKeyboard.h"
#import "NumericKeypad.h"
#import "TextFieldHandler.h"
#import "UIColor+Presets.h"
#import "UIDevice+Utilities.h"
#import "UIImage+Alpha.h"
#import "UIImage+Resize.h"
#import "UIImage+RoundedCorner.h"
#import "UIImage+Cache.h"
#import "UITextField+TextHandler.h"
#import "UIView+Shortcuts.h"
#import "UIView+Utilities.h"
#import "UIViewController+Embedding.h"
#import "UIViewController+QueuedModal.h"
#import "UIViewController+Utilities.h"
#import "UIWindow+Utilities.h"
#import "IZAnalytics.h"
#import "IZCarouselController.h"
#import "NSData+Encryption.h"
#import "NSMutableAttributedString+Htmlify.h"
#import "UIImage+Generate.h"
#import "CustomBarButtonItem.h"
#import "FormTableViewCell.h"
#import "UIScrollView+KeyboardAvoidance.h"
#import "NSObject+KVOHelper.h"
#import "UIBarButtonItem+Utilities.h"
#import "UIImage+FormRowImage.h"
#import "CardIssuer.h"
#import "IZCardInfo.h"
#import "UIAlertView+QuickAlert.h"
#import "OverlayNotificationView.h"
#import "UIButton+Spinner.h"
#import "NSDate+Utilities.h"
#import "CircularFileBuffer.h"
#import "NSError+Utilities.h"
#import "IZFuture.h"
#import "IZFutureQueue.h"
#import "IZFuture+Utilities.h"
#import "IZFuture+Attempt.h"
#import "NSDecimalNumber+Amount.h"
#import "NSAttributedString+Formatting.h"
#import "NSString+Formatting.h"
#import "UILabel+Formatting.h"
#import "IZNetworkContext.h"
#import "NSDecimalNumber+Utilities.h"
#import "NSArray+Utilities.h"
#import "UITableView+NiceUpdate.h"
#import "UITableViewCell+SlideToDelete.h"
#import "NSLayoutConstraint+IZettleAdditions.h"

#import "IZTheme.h"
#import "CircleProgressView.h"
#import "UIFont+CustomFonts.h"
#import "StatusView.h"

#import "FormItem.h"
#import "FormRow.h"
#import "FormGroup.h"
#import "Form.h"
#import "FormRowView.h"
#import "FormTableView.h"
#import "FormTableViewDataSource.h"
#import "Form+BasicSubmitForm.h"
#import "IZettleFormViews.h"

#import "NSObject+CachedValue.h"
#import "KeyboardVisibility.h"

#import "IZTelemetry.h"
#import "IZTelemetry+Account.h"

// FIXME: move to iZettlePayments framework +>
#import "IZTransactionTelemetry.h"
#import "IZTransactionTelemetry+CardPayments.h"
#import "IZTransactionTelemetry+Gratuity.h"
#import "IZTransactionTelemetry+RepeatPayments.h"
#import "IZTransactionTelemetry+SCA.h"
// <+

// Debug
#import "IZDebugNetworkProtocol.h"
#import "IZDebugNetworkResponseProvider.h"
#import "IZDebugNetworkResponseBuilder.h"

// Signals
#import "IZSignal.h"
#import "IZCallbacker.h"
#import "IZDisposable.h"
#import "IZDisposeBag.h"
#import "IZDisposer.h"
#import "IZPair.h"
#import "NSNotificationCenter+IZSignal.h"
#import "UIControl+IZSignal.h"

// UI Elements
#import "IZButton.h"
#import "FormItemView.h"
#import "IZLabel.h"
#import "LayerViews.h"
#import "SeparatorView.h"
#import "IZTextField.h"
#import "IZNavigationBar.h"
#import "TitleValueView.h"

// External
#import "IZReachability.h"
#import "Attempt.h"
#import "Herd.h"

#import "UIView+Viewport.h"

#import "FormController.h"
#import "UIViewController+iZettlePresentationUtil.h"

#ifdef DEBUG

#import "IZColorThemeProvider.h"
#import "IZStyling.h"

#endif
