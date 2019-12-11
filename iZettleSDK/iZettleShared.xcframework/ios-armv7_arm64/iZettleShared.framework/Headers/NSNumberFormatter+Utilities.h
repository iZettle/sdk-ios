//
//  NSNumberFormatter+Utilities.h
//  iZettleShared
//
//  Created by Jens Utbult on 2014-12-04.
//  Copyright (c) 2014 iZettle. All rights reserved.
//

@import Foundation;

@interface NSNumberFormatter (Utilities)

- (NSString *)izCurrencyString;
- (BOOL)izIsCurrencyPrefix;

@end
