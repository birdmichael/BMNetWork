//
//  BMBatchRequest.m
//  BMNetwork
//
//  Created by BirdMichael on 2017/12/30.
//  Copyright © 2017年 birdmichael. All rights reserved.
//

#import "BMBatchRequest.h"
#import "BMNetworkPrivate.h"
#import "BMBatchRequestAgent.h"
#import <objc/runtime.h>

@interface BMBatchRequest ()<BMRequestDelegate>

// Tag request finished count, 0 is start.
@property (nonatomic, assign) NSInteger finishedCount;

@end

@implementation BMBatchRequest

- (instancetype)initWithRequestArray:(NSArray<BMRequest *> *)requestArray {
    self = [super init];
    if (self) {
        _requestArray = [requestArray copy];
        _finishedCount = 0;
        for (BMRequest * req in _requestArray) {
            if (![req isKindOfClass:[BMRequest class]]) {
                BMLog(@"Error, request item must be BMRequest instance.");
                return nil;
            }
        }
        if (requestArray.count <= 0) {
            BMLog(@"Error, request array must not be empty.");
            return nil;
        }
    }
    return self;
}

- (void)start {
    if (_finishedCount > 0) {
        BMLog(@"Error! Batch request has already started.");
        return;
    }
    [[BMBatchRequestAgent sharedAgent] addBatchRequest:self];
    [self toggleAccessoriesWillStartCallBack];
    _failedRequest = nil;
    
    __weak typeof(self) weakSelf = self;
    for (BMRequest * request in _requestArray) {
        [request startWithCompletionBlockWithSuccess:^(__kindof BMRequest * _Nonnull request, id  _Nullable formattedData) {
            [weakSelf requestFinished:request];
        } failure:^(__kindof BMRequest * _Nonnull request, id  _Nullable formattedData) {
            [weakSelf requestFailed:request];
        }];
    }
}

- (void)stop {
    [self toggleAccessoriesWillStopCallBack];
    _delegate = nil;
    [self clearRequest];
    [self toggleAccessoriesDidStopCallBack];
    [[BMBatchRequestAgent sharedAgent] removeBatchRequest:self];
}

- (void)startWithCompletionBlockWithSuccess:(void (^)(BMBatchRequest *batchRequest))success
                                    failure:(void (^)(BMBatchRequest *batchRequest))failure {
    [self setCompletionBlockWithSuccess:success failure:failure];
    [self start];
}

- (void)setCompletionBlockWithSuccess:(void (^)(BMBatchRequest *batchRequest))success
                              failure:(void (^)(BMBatchRequest *batchRequest))failure {
    self.successCompletionBlock = success;
    self.failureCompletionBlock = failure;
}

- (void)clearCompletionBlock {
    // nil out to break the retain cycle.
    self.successCompletionBlock = nil;
    self.failureCompletionBlock = nil;
}

- (void)dealloc {
    [self clearRequest];
}

#pragma mark - BMRequest Call Back

- (void)requestFinished:(BMRequest *)Request {
    _finishedCount ++;
    if (_finishedCount == _requestArray.count) {
        [self toggleAccessoriesWillStopCallBack];
        if ([_delegate respondsToSelector:@selector(batchRequestFinished:)]) {
            [_delegate batchRequestFinished:self];
        }
        if (_successCompletionBlock) {
            _successCompletionBlock(self);
        }
        [self clearCompletionBlock];
        [self toggleAccessoriesDidStopCallBack];
        [[BMBatchRequestAgent sharedAgent] removeBatchRequest:self];
    }
}

- (void)requestFailed:(BMRequest *)request {
    _failedRequest = request;
    
    // If the request is fail ignored, handle the request as sucess finished.
    if (_failedRequest.ignoreFailedInBatchReqeust) {
        [self requestFinished:request];
        [request stop];
    }else {
        // Fail config.
        [self toggleAccessoriesWillStopCallBack];
        
        // Stop
        for (BMRequest *request in _requestArray) {
            [request stop];
        }
        // Callback
        if ([_delegate respondsToSelector:@selector(batchRequestFailed:)]) {
            [_delegate batchRequestFailed:self];
        }
        if (_failureCompletionBlock) {
            _failureCompletionBlock(self);
        }
        // Clear
        [self clearCompletionBlock];
        
        [self toggleAccessoriesDidStopCallBack];
    }
}

- (void)clearRequest {
    for (BMRequest * request in _requestArray) {
        request.delegate = nil;
        [request stop];
    }
    [self clearCompletionBlock];
}

#pragma mark - Request Accessoies

- (void)addAccessory:(id<BMRequestAccessory>)accessory {
    if (!self.requestAccessories) {
        self.requestAccessories = [NSMutableArray array];
    }
    [self.requestAccessories addObject:accessory];
}

@end




@implementation BMRequest (BatchRequest)

- (BOOL)ignoreFailedInBatchReqeust {
    return [objc_getAssociatedObject(self, _cmd) boolValue];
}

- (void)setIgnoreFailedInBatchReqeust:(BOOL)ignoreFailedInBatchReqeust {
    objc_setAssociatedObject(self, @selector(ignoreFailedInBatchReqeust), @(ignoreFailedInBatchReqeust), OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

@end
