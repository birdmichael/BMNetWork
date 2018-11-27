//
//  BMNetworkConfig.h
//  BMNetwork
//
//  Created by BirdMichael on 2017/12/30.
//  Copyright © 2017年 birdmichael. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class BMRequest;
@class AFSecurityPolicy;
@protocol BMResponseFilter;

/**
 BMUrlFilterProtocol can be used to append common parameters to requests before sending them.
 */
@protocol BMUrlFilterProtocol <NSObject>
/**
 Preprocess request URL before actually sending them.
 
 @param originUrl request's origin URL, which is returned by `requestUrl`
 @param request   request itself
 
 @return A new url which will be used as a new `requestUrl`
 */
- (NSString *)filterUrl:(NSString *)originUrl withRequest:(BMRequest *)request;
@end

/**
 BMCacheDirPathFilterProtocol can be used to append common path components when caching response results
 */
@protocol BMCacheDirPathFilterProtocol <NSObject>
/**
 Preprocess cache path before actually saving them.
 
 @param originPath original base cache path, which is generated in `BMRequest` class.
 @param request    request itself
 
 @return A new path which will be used as base path when caching.
 */
- (NSString *)filterCacheDirPath:(NSString *)originPath withRequest:(BMRequest *)request;
@end

/**
 BMNetworkConfig stored global network-related configurations, which will be used in `BMNetworkAgent`
 to form and filter requests, as well as caching response.
 */
@interface BMNetworkConfig : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 Return a shared config object.
 */
+ (BMNetworkConfig *)sharedConfig;


/**
 Request base URL, such as "http://www.example.com". Default is empty string.
 */
@property (nonatomic, strong) NSString *baseUrl;

/**
 Request CDN URL. Default is empty string.
 */
@property (nonatomic, strong) NSString *cdnUrl;

/**
 URL filters. See also `BMUrlFilterProtocol`.
 */
@property (nonatomic, strong, readonly) id<BMUrlFilterProtocol> urlFilter;

/**
 Response result filters. See also `BMResponseFilter`.
 Note that, only the `dataFilter` of a request is nil, this property will be effect.
 */
@property (nonatomic, strong, readonly) id<BMResponseFilter> dataFilter;

/**
 Cache path filters. See also `BMCacheDirPathFilterProtocol`.
 */
@property (nonatomic, strong, readonly) NSArray<id<BMCacheDirPathFilterProtocol>> *cacheDirPathFilters;

/**
 Security policy will be used by AFNetworking. See also `AFSecurityPolicy`.
 */
@property (nonatomic, strong) AFSecurityPolicy *securityPolicy;

/**
 Whether to log debug info. Default is NO;
 */
@property (nonatomic) BOOL debugLogEnabled;

/**
 SessionConfiguration will be used to initialize AFHTTPSessionManager. Default is nil.
 */
@property (nonatomic, strong) NSURLSessionConfiguration* sessionConfiguration;

/// Add a new URL filter.
- (void)addUrlFilter:(id<BMUrlFilterProtocol>)filter;

/// Remove all URL filters.
- (void)clearUrlFilter;

/// Add a new response filter.
- (void)addResponseFilter:(id<BMResponseFilter>)filter;

/// Remove all response filters.
- (void)clearResponselFilter;

/// Add a new cache path filter
- (void)addCacheDirPathFilter:(id<BMCacheDirPathFilterProtocol>)filter;

/// Clear all cache path filters.
- (void)clearCacheDirPathFilter;

@end

NS_ASSUME_NONNULL_END
