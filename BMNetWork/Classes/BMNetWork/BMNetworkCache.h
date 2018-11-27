//
//  BMNetworkCache.h
//  BMNetwork
//
//  Created by BirdMichael on 2017/12/30.
//  Copyright © 2017年 birdmichael. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BMRequest.h"

FOUNDATION_EXPORT NSString *const BMRequestCacheErrorDomain;

/// Cahe error type.
typedef NS_ENUM(NSInteger, BMRequestCacheError) {
    BMRequestCacheErrorInvalidMetadata = -1,
    BMRequestCacheErrorInvalidCacheData = -2,
};


@interface BMNetworkCache : NSObject

/**
 Returns global shared cache instance
 
 @return BMNetworkCache global instance
 */
+ (instancetype)sharedCache;

/**
 Init a new cache store with a specific namespace
 
 @param cachePath The cache path name to use for this cache store
 */
- (instancetype)initWithCachePath:(NSString *)cachePath;

/**
 Store data by the request which owned it.
 
 @param data Data of the request's response data. It will be store to cache by the request.
 @param request Request which to cache.
 */
- (void)cacheData:(NSData *)data forRequest:(BMRequest *)request;

/**
 Load cached data with a request synchronously.
 
 @param request Request used to query the data
 */
- (BOOL)loadCacheDataWithRequest:(BMRequest *)request error:(NSError * __autoreleasing *)error;

/**
 Delete cached data of the request.
 
 @param request Request used to delete the cached data
 */
- (void)deleteCacheWithRequest:(BMRequest *)request;

/**
 Clean all cached requet data under the default cache path.
 */
- (void)clearCache;

@end


/**
 Category of BMRequest, this define some config of cache.
 */
@interface BMRequest (Cache)

@property (nonatomic, strong) NSData *cacheData;
@property (nonatomic, strong) NSString *cacheString;
@property (nonatomic, strong) id cacheJSON;
@property (nonatomic, strong) NSXMLParser *cacheXML;

/**
 Whether to use cache as response or not.
 Default is NO, means the response will be cached when completed. And the response will load data from
 cache when request failed if has cached data.
 */
@property (nonatomic, assign) BOOL ignoreCache;

/**
 Default is nil

 If it is not nil, the keys in the array will be ignored for create cache path.
 */
@property (nonatomic, strong) NSArray <NSString *>*ignoreArgumentKeys;

/**
 Whether cache is asynchronously written to storage. Default is YES.
 */
@property (nonatomic, assign) BOOL writeCacheAsynchronously;

/**
 This indicate if the data is load from cache when request completed.
 */
@property (nonatomic, readonly, getter=isDataFromCache) BOOL dataFromCache;


/**
 Manually load cache from storage.
 
 @param error If an error occurred causing cache loading failed, an error object will be passed, otherwise NULL.
 
 @return Whether cache is successfully loaded.
 */
- (BOOL)loadCacheWithError:(NSError * __autoreleasing *)error;

/**
 Start request without reading local cache even if it exists. Use this to update local cache.
 */
- (void)startWithoutCache;

/**
 Save response data to this request's cache location
 */
- (void)saveResponseDataToCacheFile:(NSData *)data;

@end
