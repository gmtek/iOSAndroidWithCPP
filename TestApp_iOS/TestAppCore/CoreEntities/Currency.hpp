//
//  Currency.hpp
//  TestApp
//
//  Created by Gulshan Mandal on 22/12/2017.
//  Copyright © 2017 Gulshan Mandal. All rights reserved.
//

#ifndef Application_hpp
#define Application_hpp

#include <stdio.h>
#include <string>
#include <cstring>
#include "NetworkInterface.hpp"
#include <functional>
#include <stdarg.h>  // For va_start, etc.
#include <memory>    // For std::unique_ptr

typedef void (*CallBackAction)(void *sender, std::string name);

class Currency {
private:
    NetworkInterface *_handler;
    Currency();
    template<typename ... Args>
    std::string string_format(const std::string fmt_str, ...);
public:
    Currency(NetworkInterface *handler);
    void getRate(void *sender, CallBackAction callBack, std::string fromCurrency, std::string toCurrency);
};

#endif /* Application_hpp */
