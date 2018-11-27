//
//  BMNetworkPrivate.h
//  BMNetwork
//
//  Created by BirdMichael on 2017/12/30.
//  Copyright © 2017年 birdmichael. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BMRequest.h"
#import "BMBatchRequest.h"
#import "BMNetworkAgent.h"
#import "BMNetworkConfig.h"

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT void BMLog(NSString *format, ...) NS_FORMAT_FUNCTION(1,2);

@class AFHTTPSessionManager;

@interface BMNetworkUtils : NSObject

+ (BOOL)validateJSON:(id)json withValidator:(id)jsonValidator;

+ (void)addDoNotBackupAttribute:(NSString *)path;

+ (NSString *)md5StringFromString:(NSString *)string;

+ (NSString *)appVersionString;

+ (NSStringEncoding)stringEncodingWithRequest:(BMRequest *)request;

+ (BOOL)validateResumeData:(NSData *)data;

@end

@interface BMRequest (Getter)

@property (nonatomic, weak, readonly) id<BMRequest> child;
- (NSString *)cacheBasePath;

@end

@interface BMRequest (Setter)

@property (nonatomic, strong, readwrite) NSURLSessionTask *requestTask;
@property (nonatomic, strong, readwrite, nullable) NSData *responseData;
@property (nonatomic, strong, readwrite, nullable) id responseJSONObject;
@property (nonatomic, strong, readwrite, nullable) id responseObject;
@property (nonatomic, strong, readwrite, nullable) NSString *responseString;
@property (nonatomic, strong, readwrite, nullable) NSError *error;

@end

@interface BMRequest (RequestAccessory)

- (void)toggleAccessoriesWillStartCallBack;
- (void)toggleAccessoriesWillStopCallBack;
- (void)toggleAccessoriesDidStopCallBack;

@end

@interface BMBatchRequest (RequestAccessory)

- (void)toggleAccessoriesWillStartCallBack;
- (void)toggleAccessoriesWillStopCallBack;
- (void)toggleAccessoriesDidStopCallBack;

@end

@interface BMNetworkAgent (Private)

- (AFHTTPSessionManager *)manager;
- (void)resetURLSessionManager;
- (void)resetURLSessionManagerWithConfiguration:(NSURLSessionConfiguration *)configuration;

- (NSString *)incompleteDownloadTempCacheFolder;

@end

NS_ASSUME_NONNULL_END
