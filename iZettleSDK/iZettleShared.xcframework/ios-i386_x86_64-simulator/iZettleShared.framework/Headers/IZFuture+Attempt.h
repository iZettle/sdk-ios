//
//  IZFuture+Herd.h
//  iZettleShared
//
//  Created by Mattias Jähnke on 2015-09-10.
//  Copyright © 2015 iZettle. All rights reserved.
//

@import Foundation;
#import "IZFuture+Utilities.h"

@class Attempt;

@interface IZFuture (Attempt)

+ (IZFuture *)runAttempt:(Attempt *)attempt function:(IZFuture *(^)(Attempt *attempt))function;

@end
