//
//  KeyboardVisibility.h
//  iZettleShared
//
//  Created by Mattias Jähnke on 2013-09-23.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import Foundation;

@interface KeyboardVisibility : NSObject
+ (KeyboardVisibility *)sharedInstance;
@property (nonatomic, readonly, getter=isVisible) BOOL visible;
@end
