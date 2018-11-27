//
//  BMGeneralRequest.m
//  BMNetwork
//
//  Created by BirdMichael on 2018/1/2.
//  Copyright © 2018年 birdmichael. All rights reserved.
//

#import "BMGeneralRequest.h"

@implementation BMGeneralRequest

- (void)startWithRequestUrl:(NSString *)url arguments:(id)arguments {
    _requestUrl = url;
    _requestArgument = arguments;
    [self start];
}

- (void)startWithRequestUrl:(NSString *)url
                  arguments:(id)arguments
 completionBlockWithSuccess:(nullable BMRequestCompletionBlock)success
                    failure:(nullable BMRequestCompletionBlock)failure {
    _requestUrl = url;
    _requestArgument = arguments;
    [self startWithCompletionBlockWithSuccess:success failure:failure];
}

@end
