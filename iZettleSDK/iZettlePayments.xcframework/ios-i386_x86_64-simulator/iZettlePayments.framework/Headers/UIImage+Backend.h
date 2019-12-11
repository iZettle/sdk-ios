//
//  UIImage+Backend.h
//  iZettle
//
//  Created by Måns Bernhardt on 2011-11-03.
//  Copyright (c) 2011 iZettle. All rights reserved.
//

@import UIKit;
@import iZettleShared;

NS_ASSUME_NONNULL_BEGIN

@interface UIImage (BackendLookupKey)

@property (nonatomic, readonly) NSString *izBackendSha1LookupKey;
@property (nonatomic, readonly) NSData *izCompressedImageData;
@property (nonatomic, readonly) BOOL izIsUploaded;

- (void)izMarkAsUploaded;

@end

NS_ASSUME_NONNULL_END
