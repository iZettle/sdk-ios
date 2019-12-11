//
//  CircleProgressView.h
//
//  Created by Mattias Jähnke on 2014-10-28.
//  Copyright (c) 2014 iZettle. All rights reserved.
//

@import UIKit;

typedef enum  {
    CircleProgressTypeProgress,
    CircleProgressTypeInfinity,
    CircleProgressTypeHybrid
} CircleProgressType;

@interface CircleProgressView : UIView

// This value returns -1 if progressType is Inifite
@property (nonatomic, readwrite) CGFloat value;

@property (nonatomic, assign) CGFloat lineThickness;
@property (nonatomic, strong) UIColor *filledCircleColor;
@property (nonatomic, strong) UIColor *backCircleColor;
@property (nonatomic, assign) BOOL drawCheckmarkOnComplete;

@property (nonatomic, assign) CircleProgressType progressType;

@end