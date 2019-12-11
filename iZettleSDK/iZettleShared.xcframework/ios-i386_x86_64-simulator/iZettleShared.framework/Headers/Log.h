/*
 *  IZLog.h
 *  Runner
 *
 *  Created by Måns Bernhardt on 1/12/11.
 *  Copyright 2011 iZettle. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN


#if defined(__cplusplus)
#define IZETTLE_EXTERN extern "C"
#else
#define IZETTLE_EXTERN extern
#endif


// TODO: Remove TypeCount
typedef NS_ENUM(NSUInteger, IZLogType) {
    IZLogTypeWarning, // assert, NSErrors and other critical logging
    IZLogTypeTransaction, // transaction to and from our servers
    IZLogTypeTransactionCurl, // print curl commands
    IZLogTypeInfo, // Info useful for tracking down bugs and crashes
    IZLogTypeReader, // readers logging
    IZLogTypeDebug, // logging used when developing
    IZLogTypeTelemetry, // Telemetry events logging
    IZLogTypeBluetooth
};

IZETTLE_EXTERN void izLog(IZLogType logType, const char *filename, int lineNumber, const char *functionName, NSString *format, ...);
IZETTLE_EXTERN void izAssert(const char *filename, int lineNumber, const char *functionName, const char *expression, NSString *format, ...);

IZETTLE_EXTERN void izLogTiming(const char *filename, int lineNumber, const char *functionName, dispatch_block_t timerBlock,  NSString *format, ...);

IZETTLE_EXTERN void (^ _Nullable izLogBlock)(IZLogType logType, NSString *fileName, NSString *functionName, NSInteger lineNumber, NSString *logString);


#define IZLogDebug(...) izLog(IZLogTypeDebug, __FILE__,__LINE__,__FUNCTION__,__VA_ARGS__)
#define IZLogReader(...) izLog(IZLogTypeReader, __FILE__,__LINE__,__FUNCTION__,__VA_ARGS__)
#define IZLogInfo(...) izLog(IZLogTypeInfo, __FILE__,__LINE__,__FUNCTION__,__VA_ARGS__)
#define IZLogTransaction(...) izLog(IZLogTypeTransaction, __FILE__,__LINE__,__FUNCTION__,__VA_ARGS__)
#define IZLogTransactionCurl(...) izLog(IZLogTypeTransactionCurl, __FILE__,__LINE__,__FUNCTION__,__VA_ARGS__)
#define IZLogWarning(...) izLog(IZLogTypeWarning, __FILE__,__LINE__,__FUNCTION__,__VA_ARGS__)
#define IZLogTelemetry(...) izLog(IZLogTypeTelemetry, __FILE__,__LINE__,__FUNCTION__,__VA_ARGS__)
#define IZLogBluetooth(...) izLog(IZLogTypeBluetooth, __FILE__,__LINE__,__FUNCTION__,__VA_ARGS__)

#define IZLogWithType(type, ...) izLog(type,__FILE__,__LINE__,__FUNCTION__,__VA_ARGS__)
#define IZLog(...) izLog(IZLogTypeDebug,__FILE__,__LINE__,__FUNCTION__,__VA_ARGS__)
#define IZLogTiming(block, ...) izLogTiming(__FILE__,__LINE__,__FUNCTION__, block,__VA_ARGS__)
#define IZAssert(expression, ...) izAssert(__FILE__,__LINE__,__FUNCTION__,expression,__VA_ARGS__)

#if 0
#define IZDealloc(...) izLog(IZLogTypeDebug,__FILE__,__LINE__,__FUNCTION__,__VA_ARGS__)
#else
#define IZDealloc(...) while(0);
#endif

#undef NSLog
#undef assert
#undef NSAssert

#define NSLog(...) do { IZLogInfo(__VA_ARGS__); } while(0);
#define assert(e) (__builtin_expect(!(e), 0) ? IZAssert(#e, @"") : (void)0)
#define NSAssert(e, ...) (__builtin_expect(!(e), 0) ? IZAssert(#e,__VA_ARGS__) : (void)0)


#if defined(DEBUG) && !defined(NDEBUG)

    #define TimeBlock(block, ...) do { IZLogTiming(block, __VA_ARGS__); } while(0);

#else

    #define TimeBlock(block, ...) block();

#endif

#ifdef DEBUG

#define DLog(...) do {  IZLogDebug(__VA_ARGS__);  } while(0);
#define NDLog(...) do { } while(0);

#else

#define DLog(...) do { } while(0);
#define NDLog(...) { IZLogDebug(__VA_ARGS__);  } while(0);

#endif

NS_ASSUME_NONNULL_END

