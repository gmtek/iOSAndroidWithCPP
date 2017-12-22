//
//  NwImplShort.cpp
//  TestApp
//
//  Created by Gulshan Mandal on 22/12/2017.
//  Copyright © 2017 Gulshan Mandal. All rights reserved.
//

#include "NwImplShort.hpp"
#include <Foundation/Foundation.h>

void NwImplShort::execute(std::string urlString, std::string httpMethod, std::function<void(int statusCode, std::string response)> callBack) {
    
    NSURLSessionConfiguration *configuration = [NSURLSessionConfiguration defaultSessionConfiguration];
    NSURLSession *session = [NSURLSession sessionWithConfiguration:configuration delegate:nil delegateQueue:nil];
    NSURL *url = [NSURL URLWithString:[NSString stringWithCString:urlString.c_str() encoding:[NSString defaultCStringEncoding]]];
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:url
                                                           cachePolicy:NSURLRequestUseProtocolCachePolicy
                                                       timeoutInterval:60.0];
    
    [request addValue:@"application/json" forHTTPHeaderField:@"Content-Type"];
    [request addValue:@"application/json" forHTTPHeaderField:@"Accept"];
    
    [request setHTTPMethod:[NSString stringWithCString:httpMethod.c_str() encoding:[NSString defaultCStringEncoding]]];
    
    NSURLSessionDataTask *postDataTask = [session dataTaskWithRequest:request completionHandler:^(NSData *data, NSURLResponse *response, NSError *error) {
                                          
                                    if (!error) {
                                          NSString *responseString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
                                          std::string responseCString = std::string([responseString UTF8String]);
                                          fprintf(stderr, "%s", [responseString UTF8String]);
                                          callBack(200, responseCString);
                                          
                                    } else {
                                        // error from the session...maybe log it here, too
                                        callBack((int)error.code, nil);
                                    }
                            }];
    [postDataTask resume];
}
