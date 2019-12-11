//
//  IZCardReaderModel.h
//  iZettlePayments
//
//  Created by Andrei Valkovskii on 2018-06-18.
//  Copyright © 2018 iZettle. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, IZCardReaderModel) {
    IZCardReaderModelUnknown = 0,
    IZCardReaderModelMiura,
    IZCardReaderModelMiuraContactless,
    IZCardReaderModelXAC,
    IZCardReaderModelDatecs,
    IZCardReaderModelDatecsNoContactless,
    IZCardReaderModelDatecsV2
};

NSString * _Nullable iz_readerIdentifierForModel(IZCardReaderModel model) NS_SWIFT_NAME(readerIdentifier(for:));
IZCardReaderModel iz_cardReaderModelForIdentifier(NSString * identifier) NS_SWIFT_NAME(readerModel(for:));

NS_ASSUME_NONNULL_END
