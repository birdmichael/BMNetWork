//
//  BMRequestProtocol.h
//  BMNetwork
//
//  Created by BirdMichael on 2018/1/5.
//  Copyright © 2018年 birdmichael. All rights reserved.
//

#ifndef BMRequestProtocol_h
#define BMRequestProtocol_h

NS_ASSUME_NONNULL_BEGIN

@class BMRequest;
/**
 The BMResponseFilter protocol defines several optional methods that can be used for
 filter the raw response data. You can use these method to convert the original response
 to RPC response object.
 */
@protocol BMResponseFilter <NSObject>

/**
 Called on background thread after request succeded.
 
 @return  return the filtered RPC json object.
          eg. original response is:
            {
                "data" : {
                    "list" : []
                },
                "ts" : time,
                "code" : custom_code
            }
 
          filtered result is:
            {
                "list" : []
            }
 */
- (nullable id)filteredResultWithRequest:(__kindof BMRequest *)request;

/**
 Override this method to define the custom error.
 
 @return  return the custom rpc error, this error may be defined by your service.
 */
- (nullable NSError *)filteredErrorWithRequest:(__kindof BMRequest *)request;

@end



/**
 The BMResponseFormatter protocol defines several optional methods that can be
 used for formatting the response data. You can use these method to convert the response
 json to target model.
 */
@protocol BMResponseFormatter <NSObject>

@optional
/**
 Called on background thread after request succeded but before switching to main thread. Note if
 the request is failed for http, the cached data will be used instead.
 
 @return  return the formatted data, it can be the final model or reformed dictionary.
 */
- (nullable id)formattedDataAfterRequestCompletePreprocessor:(__kindof BMRequest *)request;

/**
 Called on the main thread after request succeeded.
 If both implement mehtod `formattedDataAfterRequestCompletePreprocessor`, the formatted data will be
 replaced by below method.
 
 @return  return the formatted data, it can be the final model or reformed dictionary.
 */
- (nullable id)formattedDataAfterRequestCompleteFilter:(__kindof BMRequest *)request;

/**
 Called on background thread after request failed but before switching to main thread. See also
 `requestCompletePreprocessor`.
 */
- (void)requestFailedPreprocessor:(__kindof BMRequest *)request;

/**
 Called on the main thread when request failed.
 */
- (void)requestFailedFilter:(__kindof BMRequest *)request;

@end




/**
 The BMRequestAccessory protocol defines several optional methods that can be
 used to track the status of a request. Objects that conforms this protocol
 ("accessories") can perform additional configurations accordingly. All the
 accessory methods will be called on the main queue.
 */
@protocol BMRequestAccessory <NSObject>

@optional
/**
 Inform the accessory that the request is about to start.
 
 @param request The corresponding request.
 */
- (void)requestWillStart:(id)request;

/**
 Inform the accessory that the request is about to stop. This method is called
 before executing `requestFinished` and `successCompletionBlock`.
 
 @param request The corresponding request.
 */
- (void)requestWillStop:(id)request;

/**
 Inform the accessory that the request has already stoped. This method is called
 after executing `requestFinished` and `successCompletionBlock`.
 
 @param request The corresponding request.
 */
- (void)requestDidStop:(id)request;

@end


NS_ASSUME_NONNULL_END

#endif /* BMRequestProtocol_h */
