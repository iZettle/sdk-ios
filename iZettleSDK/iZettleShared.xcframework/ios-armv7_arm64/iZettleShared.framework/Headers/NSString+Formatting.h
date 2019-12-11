//
//  NSString+Formatting.h
//  iZettleShared
//
//  Created by Jens Utbult on 2014-11-27.
//  Copyright (c) 2014 iZettle. All rights reserved.
//

@import Foundation;
@import UIKit;

@interface NSString (Formatting)

- (NSAttributedString *)izPrettyFormattedAttributedStringWithFont:(UIFont *)font prefix:(NSString *)prefix suffix:(NSString *)suffix;

@end
