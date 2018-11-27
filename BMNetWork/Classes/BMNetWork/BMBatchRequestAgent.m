//
//  BMBatchRequestAgent.m
//  BMNetwork
//
//  Created by BirdMichael on 2018/1/2.
//  Copyright © 2018年 birdmichael. All rights reserved.
//

#import "BMBatchRequestAgent.h"
#import "BMBatchRequest.h"

@interface BMBatchRequestAgent()

@property (strong, nonatomic) NSMutableArray<BMBatchRequest *> *requestArray;

@end

@implementation BMBatchRequestAgent

+ (BMBatchRequestAgent *)sharedAgent {
    static id sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[self alloc] init];
    });
    return sharedInstance;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        _requestArray = [NSMutableArray array];
    }
    return self;
}

- (void)addBatchRequest:(BMBatchRequest *)request {
    @synchronized(self) {
        [_requestArray addObject:request];
    }
}

- (void)removeBatchRequest:(BMBatchRequest *)request {
    @synchronized(self) {
        [_requestArray removeObject:request];
    }
}

@end
