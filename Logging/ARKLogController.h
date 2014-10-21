//
//  ARKLogController.h
//  Aardvark
//
//  Created by Dan Federman on 10/4/14.
//  Copyright (c) 2014 Square, Inc. All rights reserved.
//

@protocol ARKLogHandler;
@class ARKLogMessage;


/// Collects and persists log messages. All methods and properties on this class are threadsafe.
@interface ARKLogController : NSObject

/// Returns the instance of the log controller used by ARKLog().
+ (instancetype)defaultController;

/// Enables logging. Defaults to NO. Turning off logging does not guarantee that logging on different threads will immediately cease. Property is atomic to support multithreaded logging.
@property (atomic, assign, readwrite, getter=isLoggingEnabled) BOOL loggingEnabled;

/// Defaults to ARKLogMessage. Can be set to a subclass of ARKLogMessage. Accessor blocks on logging queue; setter is non-blocking.
@property (nonatomic, assign, readwrite) Class logMessageClass;

/// Convenience property that allows bug reporters to prefix logs with the name of the controller they came from. Defaults to nil.
@property (nonatomic, copy, readwrite) NSString *name;

/// The maximum number of logs allLogMessages should return. Defaults to 2000. Set to 0 to not store logs in memory (but still execute log block callbacks). Old messages are purged once this limit is hit. Accessor blocks on logging queue; setter is non-blocking.
@property (nonatomic, assign, readwrite) NSUInteger maximumLogMessageCount;

/// The maximum number of logs to persist to disk. Defaults to 500. Accessor blocks on logging queue; setter is non-blocking.
@property (nonatomic, assign, readwrite) NSUInteger maximumLogCountToPersist;

/// Path to the file on disk that contains peristed logs. Defaults to nil for all controllers except defaultController. Accessor blocks on logging queue; setter is non-blocking.
@property (nonatomic, copy, readwrite) NSURL *persistedLogsFileURL;

/// Controls whether appending logs also outputs to NSLog. Defaults to NO. Accessor blocks on logging queue; setter is non-blocking.
@property (nonatomic, assign, readwrite) BOOL logsToConsole;

/// Retains an object that handles logging. Log handlers are sent logController:didAppendLogMessage: every time a log is appended. Allows for easy logging to third party services (i.e. Crashlytics, Mixpanel, etc). Non-blocking call.
- (void)addLogHandler:(id <ARKLogHandler>)logHandler;

/// Releases an object that handles logging. Non-blocking call.
- (void)removeLogHandler:(id <ARKLogHandler>)logHandler;

/// Appends a log message to the logs. Non-blocking call.
- (void)appendLogMessage:(ARKLogMessage *)logMessage;

/// Creates a log message and appends a log message to the logs. Non-blocking call.
- (void)appendLogWithText:(NSString *)text image:(UIImage *)image type:(ARKLogType)type userInfo:(NSDictionary *)userInfo;

/// Creates a log message and appends it to the logs. Non-blocking call.
- (void)appendLogWithType:(ARKLogType)type userInfo:(NSDictionary *)userInfo format:(NSString *)format arguments:(va_list)argList;

/// Creates a log message and appends it to the logs. Non-blocking call.
- (void)appendLogWithType:(ARKLogType)type userInfo:(NSDictionary *)userInfo format:(NSString *)format, ... NS_FORMAT_FUNCTION(3,4);

/// Creates a log message with ARKLogTypeDefault and appends it to the logs. Non-blocking call.
- (void)appendLogWithFormat:(NSString *)format arguments:(va_list)argList;

/// Creates a log message with ARKLogTypeDefault and appends it to the logs. Non-blocking call.
- (void)appendLogWithFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(1,2);

/// Creates a log message with a screenshot and appends it to the logs. Non-blocking call.
- (void)appendScreenshotLog;

/// Returns an array of ARKLogMessage objects. Blocks on logging queue.
- (NSArray *)allLogMessages;

/// Removes all logs. Non-blocking call.
- (void)clearLogs;

@end
