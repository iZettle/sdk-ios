//
//  FormTableViewCell.h
//  iZettle
//
//  Created by Mattias Jähnke on 2013-04-26.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import UIKit;

@class FormRowView;
@class SeparatorView;

@interface FormTableViewCell : UITableViewCell

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier formRowView:(FormRowView *)formViewRow;

@property (nonatomic, assign) BOOL first;
@property (nonatomic, assign) BOOL last;
@property (nonatomic, assign) BOOL active;


@property (nonatomic, strong) FormRowView *formRowView;

// This will insert empty space between the tableView bounds and the actual cell
@property (nonatomic, assign) CGFloat cellPaddingLeft;
@property (nonatomic, assign) CGFloat cellPaddingRight;

// Helper to optimize (don't update the background image twice)
- (void)setFirst:(BOOL)first last:(BOOL)last;

- (CGFloat)cellPaddingWithWidth:(CGFloat)width;

@end