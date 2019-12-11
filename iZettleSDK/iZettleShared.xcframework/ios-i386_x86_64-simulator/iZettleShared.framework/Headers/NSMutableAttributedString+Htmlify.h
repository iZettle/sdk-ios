//
//  NSAttributedString+Htmlify.h
//  iZettle
//
//  Created by Mattias Jähnke on 2013-04-10.
//  Copyright (c) 2013 iZettle. All rights reserved.
//

@import UIKit;

@interface NSMutableAttributedString (Htmlify)

- (void)htmlifyWithBoldFont:(UIFont *)boldFont;
- (void)addAttributes:(NSDictionary *)attrs forTag:(NSString *)tag;
- (void)removeTag:(NSString *)tag;

@end
