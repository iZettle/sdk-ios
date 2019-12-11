//
//  UILabel+Formatting.h
//  iZettleShared
//
//  Created by Jens Utbult on 2014-11-27.
//  Copyright (c) 2014 iZettle. All rights reserved.
//

@import UIKit;

@interface UILabel (Formatting)

- (void)izInstallPrettyFormatterForPrefix:(NSString *)prefix suffix:(NSString *)suffix;
- (void)izInstallPrettyFormatterWithFormatter:(NSNumberFormatter *)formatter;

@end