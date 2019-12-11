//
//  Button.h
//  iZettle
//
//  Created by Mattias Jähnke on 2013-04-25.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import UIKit;

@class FormItemView;
@class DingbatLabel;

@interface IZButton : UIButton

- (void)_sharedInit;

@property (nonatomic, copy) dispatch_block_t actionBlock;
@property (nonatomic, weak) UIFont *titleLabelFont;
@property (nonatomic, assign) CGFloat minWidth;
@property (nonatomic, assign) CGFloat maxWidth;
/// Use this only for non-autolayout stuff
@property (nonatomic, assign) BOOL autoAdjustToText;

- (void)adjustToText;
- (void)removeDingbat;

@end

@interface IZPrimaryButton : IZButton
@end
@interface IZSecondaryButton : IZButton
@end

// Variants of normal size buttons
@interface ActionButton : IZButton
@end
@interface DestructiveButton : IZButton
@end
@interface DestructiveActionButton : IZButton
@end
// A button without background
@interface ClearButton : IZButton
@end

// Small buttons
@interface SmallButton : IZButton
@end

// Rounded Buttons
@interface RoundedButton : IZButton
@end
@interface RoundedActionButton : RoundedButton
@end
@interface RoundedGreenButton : RoundedButton
@end

// Special buttons

// Button without background, the title is underlined
// Note that this button will set it's colors by itself (hardcoded) to avoid issues with NSAttributedString and UIAppearance
@interface LinkButton : IZButton
@property (nonatomic, assign) BOOL underline;
@end

// Button used in Menus first row. Special to that case
@interface MultiActionButton : IZButton
@property (nonatomic, strong) NSArray *actionBlocks;
@end

// Simple button without just a dingbat and no background
@interface DingbatButton : IZButton
@end

// Buttons in dark toolbars (bottom of history / reports)
@interface ToolbarButton : IZButton
@end

// Buttons used for navigationbars in the a UIBarButtonItem.
@interface NavButton: IZButton
@end

// Buttons used for navigationbars in the a UIBarButtonItem.
@interface DestructiveNavButton: NavButton
@end
