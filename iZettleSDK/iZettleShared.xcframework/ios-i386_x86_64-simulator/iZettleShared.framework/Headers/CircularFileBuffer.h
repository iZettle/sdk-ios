//
//  CircularFileBuffer.h
//  iZettleShared
//
//  Created by Måns Bernhardt on 2014-01-14.
//  Copyright (c) 2014 iZettle. All rights reserved.
//

@import Foundation;

@class CircularFileBuffer;

//@protocol CircularFileBufferDelegate<NSObject>
//
//- (void)circularFileBufferDidSwitchFile:(CircularFileBuffer *)circularFileBuffer;
//
//@end


@interface CircularFileBuffer : NSObject

- (instancetype)initWithURL:(NSURL *)url;

@property (nonatomic, readonly) NSURL *url;
@property (nonatomic, readonly) NSURL *prevURL;

@property (nonatomic, assign) NSUInteger maxFileSize;
@property (nonatomic, readonly) unsigned long long currentFileSize;
//@property (nonatomic, weak) id<CircularFileBufferDelegate> delegate;

- (void)appendText:(NSString *)text;
- (void)switchBuffer;


@end
