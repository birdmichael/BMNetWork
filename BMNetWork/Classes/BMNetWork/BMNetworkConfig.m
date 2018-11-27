//
//  BMNetworkConfig.m
//  BMNetwork
//
//  Created by BirdMichael on 2017/12/30.
//  Copyright © 2017年 birdmichael. All rights reserved.
//

#import "BMNetworkConfig.h"
#import "BMRequest.h"

#if __has_include(<AFNetworking/AFNetworking.h>)
#import <AFNetworking/AFNetworking.h>
#else
#import "AFNetworking.h"
#endif

@implementation BMNetworkConfig {
    id<BMUrlFilterProtocol> urlFilter;
    NSMutableArray<id<BMCacheDirPathFilterProtocol>> *_cacheDirPathFilters;
}
@synthesize urlFilter = _urlFilter;

+ (BMNetworkConfig *)sharedConfig {
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
        _baseUrl = @"";
        _cdnUrl = @"";
        _securityPolicy = [AFSecurityPolicy defaultPolicy];
        _debugLogEnabled = NO;
    }
    return self;
}

- (void)addUrlFilter:(id<BMUrlFilterProtocol>)filter {
    _urlFilter = filter;
}

- (void)clearUrlFilter {
    _urlFilter = nil;
}

- (void)addResponseFilter:(id<BMResponseFilter>)filter {
    _dataFilter = filter;
}

- (void)clearResponselFilter {
    _dataFilter = nil;
}

- (void)addCacheDirPathFilter:(id<BMCacheDirPathFilterProtocol>)filter {
    if (_cacheDirPathFilters == nil) {
        _cacheDirPathFilters = [NSMutableArray arrayWithCapacity:0];
    }
    [_cacheDirPathFilters addObject:filter];
}

- (void)clearCacheDirPathFilter {
    [_cacheDirPathFilters removeAllObjects];
}

- (id<BMUrlFilterProtocol>)urlFilter {
    return _urlFilter;
}

- (NSArray<id<BMCacheDirPathFilterProtocol>> *)cacheDirPathFilters {
    return [_cacheDirPathFilters copy];
}

#pragma mark - NSObject

- (NSString *)description {
    return [NSString stringWithFormat:@"<%@: %p>{ baseURL: %@ } { cdnURL: %@ }", NSStringFromClass([self class]), self, self.baseUrl, self.cdnUrl];
}

@end
