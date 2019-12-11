//
//  IZDisposable.h
//  iZettleShared
//
//  Created by Said Sikira on 2018-04-22.
//  Copyright © 2018 iZettle. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol IZDisposable <NSObject>
@required
- (void)dispose;
@end
