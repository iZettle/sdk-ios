
// UIImage+RoundedCorner.h
// Created by Trevor Harmon on 9/20/09.
// Free for personal or commercial use, with or without modification.
// No warranty is expressed or implied.

@import UIKit;

// Extends the UIImage class to support making rounded corners
@interface UIImage (RoundedCorner)
- (UIImage *)izRoundedCornerImage:(NSInteger)cornerSize borderSize:(NSInteger)borderSize;
@end
