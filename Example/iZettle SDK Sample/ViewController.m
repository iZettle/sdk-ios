//
//  ViewController.m
//  iZettle SDK Sample
//
//  Copyright (c) 2015 iZettle. All rights reserved.
//

#import "ViewController.h"
#import <iZettleSDK/iZettleSDK.h>
#import "AmountWheel.h"
#import "ConsoleViewController.h"

@interface ViewController ()
@property (weak, nonatomic) IBOutlet UIButton *chargeButton;
@property (weak, nonatomic) IBOutlet AmountWheel *amountWheel;
@property (weak, nonatomic) IBOutlet UILabel *amountLabel;
@property (weak, nonatomic) IBOutlet UIToolbar *lastPaymentInfoToolBar;
@property (weak, nonatomic) IBOutlet UIView *dotView;
@end

@implementation ViewController {
    iZettleSDKPaymentInfo *_lastPaymentInfo;
    NSString *_lastReference;
    NSDate *_timestamp;
    NSError *_lastError;
    NSNumberFormatter *_numberFormatter;
}

#pragma mark - View lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];
    _numberFormatter = [[NSNumberFormatter alloc] init];
    _numberFormatter.minimumFractionDigits = 2;
    _numberFormatter.minimumIntegerDigits = 1;
    _amountLabel.text = [_numberFormatter stringFromNumber:_amountWheel.amount];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    _amountWheel.amountUpdatedBlock = ^(NSDecimalNumber *amount) {
        _amountLabel.text = [_numberFormatter stringFromNumber:amount];
    };
}

- (void)viewWillLayoutSubviews {
    [super viewWillLayoutSubviews];
    [self _makeViewRound:_chargeButton];
    [self _makeViewRound:_dotView];
}

#pragma mark - User interaction

- (IBAction)charge:(id)sender {
    // Note! Replace this reference with your own if you want to be able to query iZettle about payment info and perform refunds.
    _lastReference = [self _uniqueReference];
    NSDecimalNumber *amount = _amountWheel.amount;
    
    [[iZettleSDK shared] chargeAmount:amount currency:nil reference:_lastReference presentFromViewController:self completion:^(iZettleSDKPaymentInfo *paymentInfo, NSError *error) {
        _lastPaymentInfo = paymentInfo;
        _lastError = error;
        _timestamp = [NSDate date];
        
        [self _updateLastPaymentToolbar];
        [self _showConsole];
    }];
}

- (IBAction)settings:(id)sender {
    [[iZettleSDK shared] presentSettingsFromViewController:self];
}

- (IBAction)lastPaymentInfo:(id)sender {
    [[iZettleSDK shared] retrievePaymentInfoForReference:_lastReference presentFromViewController:self completion:^(iZettleSDKPaymentInfo *paymentInfo, NSError *error) {
        _lastPaymentInfo = paymentInfo;
        _lastError = error;
        [self _showConsole];
    }];
}

- (IBAction)refundLastPayment:(id)sender {
    NSString *paymentReference = _lastReference;
    _lastReference = [self _uniqueReference];
    [[iZettleSDK shared] refundPaymentWithReference:paymentReference refundReference:_lastReference presentFromViewController:self completion:^(iZettleSDKPaymentInfo *paymentInfo, NSError *error) {
        _lastPaymentInfo = paymentInfo;
        _lastError = error;
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

- (void)_makeViewRound:(UIView*)aView {
    UIBezierPath *circlePath = [UIBezierPath bezierPathWithOvalInRect:aView.bounds];
    CAShapeLayer *shape = [[CAShapeLayer alloc] init];
    [shape setPath:circlePath.CGPath];
    aView.layer.mask = shape;
}

@end
