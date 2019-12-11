//
//  StatusView.h
//  iZettle
//
//  Created by Mattias Jähnke on 2013-05-21.
//  Copyright (c) 2013 Mattias Jähnke. All rights reserved.
//

@import UIKit;
#import "LayerViews.h"
#import "IZLabel.h"

@class CircleProgressView;

@interface StatusView : MainLayer

@property (nonatomic, strong, readonly) CircleProgressView *circleProgressView;
@property (nonatomic, strong) HeadlineLabel *statusTitleTextLabel;
@property (nonatomic, strong) SubheadlineLabel *statusDescriptionTextLabel;

@end
