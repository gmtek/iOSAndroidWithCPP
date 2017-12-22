//
//  NetworkInterface.hpp
//  TestApp
//
//  Created by Gulshan Mandal on 22/12/2017.
//  Copyright © 2017 Gulshan Mandal. All rights reserved.
//

#ifndef NetworkInterface_hpp
#define NetworkInterface_hpp

#include <stdio.h>
#include <string>
#include <cstring>
#include <functional>

class NetworkInterface {
public:
    virtual void execute(std::string urlString, std::string httpMethod, std::function<void(int statusCode, std::string response)> callBack) = 0;
};

#endif /* NetworkInterface_hpp */
