//
//  NwImplShort.hpp
//  TestApp
//
//  Created by Gulshan Mandal on 22/12/2017.
//  Copyright © 2017 Gulshan Mandal. All rights reserved.
//

#ifndef NwImplShort_hpp
#define NwImplShort_hpp

#include <stdio.h>
#include <string>
#include <cstring>
#include "NetworkInterface.hpp"

class NwImplShort : public NetworkInterface {
public:
    void execute(std::string urlString, std::string httpMethod, std::function<void(int statusCode, std::string response)> callBack);
};

#endif /* NwImplShort_hpp */
