//
//  BMNetworkAgent.h
//  BMNetwork
//
//  Created by BirdMichael on 2017/12/30.
//  Copyright © 2017年 birdmichael. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class BMRequest;

/**
 BMNetworkAgent is the underlying class that handles actual request generation,
 serialization and response handling.
 
 It is private agent of `BMRequest`. And the function is just same as NSURLConnection.
 */
@interface BMNetworkAgent : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 Get the shared agent.
 */
+ (BMNetworkAgent *)sharedAgent;

/**
 Add request to session and start it.
 */
- (void)addRequest:(__kindof BMRequest *)request;

/**
 Cancel a request that was previously added.
 */
- (void)cancelRequest:(__kindof BMRequest *)request;

/**
 Cancel all requests that were previously added.
 */
- (void)cancelAllRequests;

/**
 Return the constructed URL of request.
 
 @param request The request to parse. Should not be nil.
 
 @return The result URL.
 */
- (NSString *)buildRequestUrl:(__kindof BMRequest *)request;

@end

NS_ASSUME_NONNULL_END
