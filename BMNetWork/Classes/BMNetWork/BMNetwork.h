//
//  BMNetwork.h
//  BMNetwork
//
//  Created by BirdMichael on 2017/12/29.
//  Copyright © 2017年 birdmichael. All rights reserved.
//
//  This component is based on YTKNetWork https://github.com/yuantiku.
//

#import <Foundation/Foundation.h>

#ifndef _BMNETWORK_
    #define _BMNETWORK_

#if __has_include(<BMNetwork/BMNetwork.h>)

    FOUNDATION_EXPORT double BMNetworkVersionNumber;
    FOUNDATION_EXPORT const unsigned char BMNetworkVersionString[];

    #import <BMNetwork/BMRequest.h>
    #import <BMNetwork/BMGeneralRequest.h>
    #import <BMNetwork/BMBatchRequest.h>
    #import <BMNetwork/BMNetworkAgent.h>
    #import <BMNetwork/BMNetworkCache.h>
    #import <BMNetwork/BMNetworkConfig.h>

#else

    #import "BMRequest.h"
    #import "BMGeneralRequest.h"
    #import "BMBatchRequest.h"
    #import "BMNetworkAgent.h"
    #import "BMNetworkCache.h"
    #import "BMNetworkConfig.h"

#endif /* __has_include */

#endif /* BMNetwork_h */

