//
//  NSAttributedString+Formatting.h
//  iZettleShared
//
//  Created by Jens Utbult on 2014-11-27.
//  Copyright (c) 2014 iZettle. All rights reserved.
//

@import UIKit;
@import Foundation;

@interface NSAttributedString (Formatting)

- (NSAttributedString *)izAttributedStringThatFitsWidth:(CGFloat)width;
- (UIFont *)izLargestCapHeightFontInAttributedString;

@end
