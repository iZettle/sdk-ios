//
//  Picker.h
//  iZettleShared
//
//  Created by Sven Röder on 5/16/13.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

#import "IZTextField.h"

@interface IZPicker : IZTextField<UITextFieldDelegate>

@property (nonatomic, strong) NSArray *options;
@property (nonatomic) NSInteger selectedIndex;

- (void)selectedIndexChangedHandler:(void (^)(NSInteger selectedIndex))block;

@end
