//
//  BMGeneralRequest.h
//  BMNetwork
//
//  Created by BirdMichael on 2018/1/2.
//  Copyright © 2018年 birdmichael. All rights reserved.
//

#import "BMRequest.h"

#ifndef BM_SUBCLASSING_RESTRICTED
#define BM_SUBCLASSING_RESTRICTED __attribute__((objc_subclassing_restricted))
#endif

NS_ASSUME_NONNULL_BEGIN

/**
 A general request inherited from BMRequest. And all the properties is confirm protocol
 `BMReqest`.
 
 This request will provide several properties for easy creating API requst.
 */
BM_SUBCLASSING_RESTRICTED
@interface BMGeneralRequest : BMRequest <BMRequest>

/// All below property is confirmed protocol `BMRequest`, more info see `BMRequest`.
@property (nonatomic, strong) NSString *baseUrl;

@property (nonatomic, strong) NSString *requestUrl;

@property (nonatomic, strong) NSString *cdnUrl;

@property (nonatomic, assign) NSTimeInterval requestTimeoutInterval;

@property (nonatomic, strong) id requestArgument;

@property (nonatomic, assign) BMRequestMethod requestMethod;

@property (nonatomic, assign) BMRequestSerializerType requestSerializerType;

@property (nonatomic, assign) BMResponseSerializerType responseSerializerType;

@property (nonatomic, strong, nullable) NSArray<NSString *> *requestAuthorizationHeaderFieldArray;

@property (nonatomic, strong, nullable) NSDictionary<NSString *, NSString *> *requestHeaderFieldValueDictionary;

@property (nonatomic, strong, nullable) NSURLRequest *buildCustomUrlRequest;

@property (nonatomic, assign) BOOL useCDN;

@property (nonatomic, assign) BOOL allowsCellularAccess;

@property (nonatomic, strong, nullable) id jsonValidator;

/**
 Start a request with `requestUrl`, `requestArgument`.
 
 @param url         used as `requestUrl`.
 
 @param arguments   used as `requestArgument`.
 */
- (void)startWithRequestUrl:(NSString *)url arguments:(id)arguments;

/**
 Convenience method to start a request with `requestUrl`, `requestArgument`, block callbacks.
 */
- (void)startWithRequestUrl:(NSString *)url
                  arguments:(id)arguments
 completionBlockWithSuccess:(nullable BMRequestCompletionBlock)success
                    failure:(nullable BMRequestCompletionBlock)failure;

@end

NS_ASSUME_NONNULL_END

