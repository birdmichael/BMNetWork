//
//  BMBatchRequest.h
//  BMNetwork
//
//  Created by BirdMichael on 2017/12/30.
//  Copyright © 2017年 birdmichael. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BMRequest.h"

NS_ASSUME_NONNULL_BEGIN

@class BMBatchRequest;

typedef void (^BMBatchRequestCompletionBlock)(__kindof BMBatchRequest *Request);

/**
 The BMBatchRequestDelegate protocol defines several optional methods you can use
 to receive network-related messages. All the delegate methods will be called
 on the main queue.
 */
@protocol BMBatchRequestDelegate <NSObject>

@optional
/**
 Tell the delegate that all the requests has finished successfully.
 
 @param Request The corresponding requests.
 */
- (void)batchRequestFinished:(__kindof BMBatchRequest *)Request;

/**
 Tell the delegate that one of the requests has failed.
 
 @param Request The corresponding requests.
 */
- (void)batchRequestFailed:(__kindof BMBatchRequest *)Request;

@end


/**
 BMBatchRequest can be used to batch several BMRequest. Note that when used inside BMBatchRequest, a single
 BMBatchRequest will have its own callback and delegate cleared, in favor of the batch request callback.
 */
@interface BMBatchRequest : NSObject

/**
 All the requests are stored in this array.
 */
@property (nonatomic, strong, readonly) NSArray<BMRequest *> *requestArray;

/**
 All the request operation are stored in this array.
 */
@property (nonatomic, strong, readonly) NSArray<BMRequest *> *RequestArray;

/**
 The delegate object of the batch request operation. Default is nil.
 */
@property (nonatomic, weak, nullable) id<BMBatchRequestDelegate> delegate;

/**
 The success callback. Note this will be called only if all the requests are finished.
 This block will be called on the main queue.
 */
@property (nonatomic, copy, nullable) void (^successCompletionBlock)(BMBatchRequest *);

/**
 The failure callback. Note this will be called if one of the requests fails.
 This block will be called on the main queue.
 */
@property (nonatomic, copy, nullable) void (^failureCompletionBlock)(BMBatchRequest *);

/**
 Tag can be used to identify batch request. Default value is 0.
 */
@property (nonatomic) NSInteger tag;

/**
 This can be used to add several accossories object. Note if you use `addAccessory` to add acceesory
 this array will be automatically created. Default is nil.
 */
@property (nonatomic, strong, nullable) NSMutableArray<id<BMRequestAccessory>> *requestAccessories;

/**
 The first request that failed (and causing the batch request to fail).
 */
@property (nonatomic, strong, readonly, nullable) BMRequest *failedRequest;

/**
 Creates a `YTKBatchRequest` with a bunch of requests.
 
 @param requestArray requests used to create batch request.
 */
- (instancetype)initWithRequestArray:(NSArray<BMRequest *> *)requestArray;

/**
 Set completion callbacks
 */
- (void)setCompletionBlockWithSuccess:(nullable void (^)(BMBatchRequest *batchRequest))success
                              failure:(nullable void (^)(BMBatchRequest *batchRequest))failure;

/**
 Nil out both success and failure callback blocks.
 */
- (void)clearCompletionBlock;

/**
 Convenience method to add request accessory. See also `requestAccessories`.
 */
- (void)addAccessory:(id<BMRequestAccessory>)accessory;

/**
 Append all the requests to queue.
 */
- (void)start;

/**
 Stop all the requests of the batch request operation.
 */
- (void)stop;

/**
 Convenience method to start the batch request with block callbacks.
 */
- (void)startWithCompletionBlockWithSuccess:(nullable void (^)(BMBatchRequest *batchRequest))success
                                    failure:(nullable void (^)(BMBatchRequest *batchRequest))failure;

@end




@interface BMRequest (BatchRequest)

/**
 Indicator that if going on other requests when this request failed. Default is NO.

 If this property is YES, the `failedRequest` of the batch request operation will be the
 last failed request. And the failed request will not break the batch request operation.
 */
@property (nonatomic, assign) BOOL ignoreFailedInBatchReqeust;

@end


NS_ASSUME_NONNULL_END
