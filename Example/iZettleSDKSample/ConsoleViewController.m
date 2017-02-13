//
//  ConsoleViewController.m
//  iZettle SDK Sample
//
//  Copyright (c) 2015 iZettle. All rights reserved.
//

#import "ConsoleViewController.h"
#import "ViewController.h"

@interface ConsoleViewController ()
@property (weak, nonatomic) IBOutlet UITextView *logTextView;
@end

@implementation ConsoleViewController

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    self.logTextView.text = _log;
    [self.logTextView setContentOffset:CGPointZero animated:YES];
}

static NSString *_log;

- (void)addToLog:(id)object {
    if (!_log) {
        _log = @"";
    }
    
    NSDate *ts = [NSDate date];
    _log = [NSString stringWithFormat:@"%@\n%@:\n%@\n\n\n%@", ts, NSStringFromClass([object class]), object, _log];
}

- (IBAction)done:(id)sender {
    [self dismissViewControllerAnimated:YES completion:nil];
}

@end
