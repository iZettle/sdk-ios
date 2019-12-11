//
//  Form+BasicSubmitForm.h
//  iZettleShared
//
//  Created by Mattias Jähnke on 2013-08-26.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import Foundation;
#import "Form.h"
#import "FormItem.h"

@interface Form (BasicSubmitForm)

- (__weak FormValueItem *)textFieldItem;
- (__weak FormActionItem *)cancelItem;
- (__weak FormActionItem *)submitItem;
- (__weak FormItem *)dingbatItem;

+ (Form *)basicSubmitFormWithTitle:(NSString *)title message:(NSString *)message textFieldDingbat:(NSString *)textFieldDingbat textFieldPlaceholder:(NSString *)placeHolder textFieldType:(FormItemType)textFieldType cancelTitle:(NSString *)cancelTitle submitTitle:(NSString *)submitTitle cancelAction:(dispatch_block_t)cancelAction submitAction:(dispatch_block_t)submitAction submitButtonType:(FormItemType)submitButtonType runValidation:(BOOL)runValidation;

@end
