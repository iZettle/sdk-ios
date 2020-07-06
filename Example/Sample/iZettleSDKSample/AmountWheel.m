//
//  AmountWheel.m
//  iZettle SDK Sample
//
//  Copyright (c) 2015 iZettle. All rights reserved.
//

#import "AmountWheel.h"
#import <UIKit/UIGestureRecognizerSubclass.h>

@interface RotationGestureRecognizer : UIGestureRecognizer

@property (nonatomic, assign) CGFloat rotation;

@end

@implementation RotationGestureRecognizer

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    if ([[event touchesForGestureRecognizer:self] count] == 1) {
        self.state = UIGestureRecognizerStateBegan;
    } else {
        self.state = UIGestureRecognizerStateFailed;
    }
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    self.state = UIGestureRecognizerStateChanged;
    
    UITouch *touch = [touches anyObject];
    
    UIView *view = self.view;
    CGPoint center = CGPointMake(CGRectGetMidX([view bounds]), CGRectGetMidY([view bounds]));
    CGPoint currentTouchPoint = [touch locationInView:view];
    CGPoint previousTouchPoint = [touch previousLocationInView:view];
    
    CGFloat angleInRadians = atan2f(currentTouchPoint.y - center.y, currentTouchPoint.x - center.x) - atan2f(previousTouchPoint.y - center.y, previousTouchPoint.x - center.x);
    
    if (angleInRadians > M_PI) {
        angleInRadians -= M_PI;
    }
    
    [self setRotation:angleInRadians];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
    self.state = UIGestureRecognizerStateEnded;
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
    self.state = UIGestureRecognizerStateCancelled;
}

@end


@implementation AmountWheel {
    CGFloat _rotation;
    CGFloat _amountIncrementor;
}

- (instancetype)initWithCoder:(NSCoder *)aDecoder {
    self = [super initWithCoder:aDecoder];
    if (self) {
        _amount = [NSDecimalNumber decimalNumberWithMantissa:1 exponent:1 isNegative:_amountIncrementor < 0];
        RotationGestureRecognizer *rotationGesture = [[RotationGestureRecognizer alloc] initWithTarget:self action:@selector(_rotate:)];
        [self addGestureRecognizer:rotationGesture];
    }
    return self;
}

- (void)_rotate:(RotationGestureRecognizer *)rotationGesture {
    if (rotationGesture.rotation < 0 && [_amount isEqual:[NSDecimalNumber zero]]) {
        return;
    }
    
    _rotation += rotationGesture.rotation;
    self.transform = CGAffineTransformMakeRotation(_rotation);
    
    _amountIncrementor += rotationGesture.rotation;
    if (_amountIncrementor < -0.05 || _amountIncrementor > 0.05) {
        NSDecimalNumber *change = [NSDecimalNumber decimalNumberWithMantissa:1 exponent:-1 isNegative:_amountIncrementor < 0];
        _amount = [_amount decimalNumberByAdding:change];
        _amountIncrementor = 0;
        if (_amountUpdatedBlock) {
            _amountUpdatedBlock(_amount);
        }
    }
}

@end
