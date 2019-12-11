//
//  FormTableView.h
//  iZettleShared
//
//  Created by Sven Röder on 5/14/13.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import UIKit;

extern NSString *const FormTableViewDidMoveToWindowNotification;
extern NSString *const FormTableViewDidGetWidthNotification;


@interface FormTableView : UITableView

// This property will only be used to calculate the height of the header and footer in the tableview.
// NOTE: This will not alter the appearance.
@property (nonatomic, strong) UIFont *headerFooterFont;

@property (nonatomic, assign) CGFloat cellPaddingLeft;
@property (nonatomic, assign) CGFloat cellPaddingRight;

@property (nonatomic, assign, getter = shouldResignWhenTapped) BOOL resignWhenTapped;

@end
