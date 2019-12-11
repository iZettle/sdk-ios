// UIImage+Resize.h
// Created by Trevor Harmon on 8/5/09.
// Free for personal or commercial use, with or without modification.
// No warranty is expressed or implied.
//
// Rewritten by Nino Höglund

@import UIKit;

@interface UIImage (Resize)

- (UIImage *)izCroppedImage:(CGRect)bounds;
- (UIImage *)izThumbnailImage:(NSInteger)thumbnailSize
          transparentBorder:(NSUInteger)borderSize
               cornerRadius:(NSUInteger)cornerRadius
       interpolationQuality:(CGInterpolationQuality)quality;
- (UIImage *)izResizedImage:(CGSize)newSize
     interpolationQuality:(CGInterpolationQuality)quality;
- (UIImage *)izResizedImageWithContentMode:(UIViewContentMode)contentMode
                                  bounds:(CGSize)bounds
                    interpolationQuality:(CGInterpolationQuality)quality;

- (UIImage *)izThumbnailOfSize:(CGSize)thumbnailSize cornerRadius:(NSUInteger)cornerRadius;

- (void)izThumbnailOfSize:(CGSize)thumbnailSize
           cornerRadius:(NSUInteger)cornerRadius 
             completion:(void (^)(UIImage *image))completion;

- (UIImage*)izImageByScalingAndCroppingForSize:(CGSize)targetSize;



- (UIImage *)izStretchableImage;
- (UIImage *)izStretchableWidthImage;

- (UIImage *)izImageScaledToSize:(CGSize)newSize;


@end
