//
//  UITableView+NiceUpdate.h
//  TableViewChange
//
//  Created by Mattias Jähnke on 2015-06-05.
//  Copyright (c) 2015 nearedge. All rights reserved.
//

@import UIKit;

@interface NSArray (IndexPathEnumeration)

- (void)izEnumerateWithRowAccessBlock:(NSArray *(^)(id section))rowAccessBlock
                           usingBlock:(void (^)(id obj, NSIndexPath *indexPath, BOOL *stop))block;

- (NSIndexPath *)izIndexPathForRow:(id)row
                    rowAccessBlock:(NSArray *(^)(id section))rowAccessBlock;

@end

@interface IZTableViewChangeOperation : NSObject

+ (NSArray *)changeOperationsFrom:(NSArray *)fromSections
                               to:(NSArray *)toSections
                   rowAccessBlock:(NSArray *(^)(id section))rowAccessBlock;

// If both from & to have a value, the operation intended is Move
@property (nonatomic, readonly) NSIndexPath *from;  // If nil - insert operation
@property (nonatomic, readonly) NSIndexPath *to;    // If nil - delete operation

@end

@interface UITableView (NiceUpdate)

- (void)izAnimateChangeOperations:(NSArray *)operations
                 withRowAnimation:(UITableViewRowAnimation)rowAnimation;

@end
