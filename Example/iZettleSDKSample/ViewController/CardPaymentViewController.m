//
//  ViewController.m
//  iZettle SDK Sample
//
//  Copyright © 2015 PayPal Inc. All rights reserved.
//

#import "CardPaymentViewController.h"
#import "ConsoleViewController.h"

@import iZettleSDK;

@interface CardPaymentViewController ()
@property (weak, nonatomic) IBOutlet UILabel *amountLabel;
@property (weak, nonatomic) IBOutlet UIStepper *stepper;
@property (weak, nonatomic) IBOutlet UIToolbar *lastPaymentInfoToolBar;
@property (weak, nonatomic) IBOutlet UISwitch *tippingSwitch;
@end

@implementation CardPaymentViewController {
    iZettleSDKPaymentInfo *_lastPaymentInfo;
    NSString *_lastReference;
    NSDate *_timestamp;
    NSError *_lastError;
}

#pragma mark - View lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];
    self.amountLabel.text = @"10.0";
    self.stepper.value = self.amountLabel.text.doubleValue;
}

#pragma mark - User interaction

- (IBAction)stepperValueChanged:(UIStepper *)sender {
    _amountLabel.text = [NSString stringWithFormat: @"%.1f", sender.value];
}

- (IBAction)charge:(id)sender {
    // Note! Replace this reference with your own if you want to be able to query iZettle about payment info and perform refunds.
    _lastReference = [self _uniqueReference];
    NSDecimalNumber *amount = [NSDecimalNumber decimalNumberWithString: _amountLabel.text];
    
    [[iZettleSDK shared] chargeAmount:amount enableTipping:self.tippingSwitch.isOn reference:_lastReference presentFromViewController:self completion:^(iZettleSDKPaymentInfo *paymentInfo, NSError *error) {
        self->_lastPaymentInfo = paymentInfo;
        self->_lastError = error;
        self->_timestamp = [NSDate date];
        
        [self _updateLastPaymentToolbar];
        [self _showConsole];
    }];
}

- (IBAction)lastPaymentInfo:(id)sender {
    [[iZettleSDK shared] retrievePaymentInfoForReference:_lastReference presentFromViewController:self completion:^(iZettleSDKPaymentInfo *paymentInfo, NSError *error) {
        self->_lastPaymentInfo = paymentInfo;
        self->_lastError = error;
        [self _showConsole];
    }];
}

- (IBAction)refundLastPayment:(id)sender {
    NSString *paymentReference = _lastReference;
    _lastReference = [self _uniqueReference];
    
    [[iZettleSDK shared] refundAmount:nil ofPaymentWithReference:paymentReference refundReference:_lastReference presentFromViewController:self completion:^(iZettleSDKPaymentInfo * _Nullable paymentInfo, NSError * _Nullable error) {
        self->_lastPaymentInfo = paymentInfo;
        self->_lastError = error;
        [self _showConsole];
    }];
}

#pragma mark - Segue handling

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([[segue identifier] isEqualToString: @"showConsole"] && sender == self) {
        ConsoleViewController *console = segue.destinationViewController;
        if (_lastError) {
            [console addToLog:_lastError];
        } else {
            [console addToLog:_lastPaymentInfo];
        }
    }
}

#pragma mark - Helpers

- (void)_updateLastPaymentToolbar {
    _lastPaymentInfoToolBar.hidden = !(_lastPaymentInfo && _lastPaymentInfo.description);
    if (!_lastPaymentInfoToolBar.hidden) {
        UIBarButtonItem *lastPaymentButton = [_lastPaymentInfoToolBar.items firstObject];
        NSDateFormatter *dateFormatter = [NSDateFormatter new];
        dateFormatter.dateStyle = NSDateFormatterNoStyle;
        dateFormatter.timeStyle = NSDateFormatterMediumStyle;
        lastPaymentButton.title = [NSString stringWithFormat:@"Last payment, %@", [dateFormatter stringFromDate:_timestamp]];
    }
}

- (void)_showConsole {
    [self performSegueWithIdentifier:@"showConsole" sender:self];
}

- (NSString *)_uniqueReference {
    return [[NSUUID UUID] UUIDString];
}

@end
