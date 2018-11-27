//
//  BMBatchRequestAgent.h
//  BMNetwork
//
//  Created by BirdMichael on 2018/1/2.
//  Copyright © 2018年 birdmichael. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class BMBatchRequest;

/**
 BMBatchRequestAgent handles batch request management. It keeps track of all
 the batch requests.
 */
@interface BMBatchRequestAgent : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 Get the shared batch request agent.
 */
+ (BMBatchRequestAgent *)sharedAgent;

/**
 Add a batch request.
 */
- (void)addBatchRequest:(BMBatchRequest *)request;

/**
 Remove a previously added batch request.
 */
- (void)removeBatchRequest:(BMBatchRequest *)request;

@end

NS_ASSUME_NONNULL_END
