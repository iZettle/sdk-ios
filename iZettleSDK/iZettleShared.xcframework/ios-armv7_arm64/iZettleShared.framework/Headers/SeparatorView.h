//
//  SeparatorView.h
//  iZettle
//
//  Created by Mattias Jähnke on 2013-04-30.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import UIKit;

@interface SeparatorView : UIView

+ (SeparatorView *)separatorView;

@property (nonatomic, strong) UIColor *separatorColor UI_APPEARANCE_SELECTOR;
@property (nonatomic, strong) UIColor *highlightedSeparatorColor UI_APPEARANCE_SELECTOR;

- (void)setHighlighted:(BOOL)highlighted;

@end


@interface CellSeparatorView : SeparatorView
@end