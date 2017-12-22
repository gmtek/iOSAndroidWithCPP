//
//  Currency.cpp
//  TestApp
//
//  Created by Gulshan Mandal on 22/12/2017.
//  Copyright © 2017 Gulshan Mandal. All rights reserved.
//

#include "Currency.hpp"
#include "json.hpp"
using json = nlohmann::json;

Currency::Currency(NetworkInterface *handler) {
    _handler = handler;
}

template<typename ... Args>
std::string Currency::string_format(const std::string fmt_str, ...) {
    int final_n, n = ((int)fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
    std::unique_ptr<char[]> formatted;
    va_list ap;
    while(1) {
        formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
        strcpy(&formatted[0], fmt_str.c_str());
        va_start(ap, fmt_str);
        final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
        va_end(ap);
        if (final_n < 0 || final_n >= n)
            n += abs(final_n - n + 1);
        else
            break;
    }
    return std::string(formatted.get());
}

void Currency::getRate(void *sender, CallBackAction callBack, std::string fromCurrency, std::string toCurrency) {
    
    std::function<void (int status, std::string result)> lambda = [=](int status, std::string result) {
        
        if(200 == status) {
            auto data = json::parse(result);
            float rate = data["rates"][toCurrency];
            callBack(sender, std::to_string(rate));
        }
        else {
            callBack(sender, "Oops...Try again");
        }
    };
    
    std::string urlString = this->string_format("https://api.fixer.io/latest?symbols=%s&base=%s", toCurrency.c_str(),fromCurrency.c_str());
    _handler->execute(urlString, "GET", lambda);
}
