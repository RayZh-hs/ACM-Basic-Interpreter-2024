//
// Created by Rayzh on 2024/11/30.
//

#include "errorReporter.hpp"

void braise(BException exception) {
    if (exception == DIVIDE_BY_ZERO) {
        std::cout << "DIVIDE BY ZERO" << std::endl;
    }
    else if (exception == INVALID_NUMBER) {
        std::cout << "INVALID NUMBER" << std::endl;
    }
    else if (exception == VARIABLE_NOT_DEFINED) {
        std::cout << "VARIABLE NOT DEFINED" << std::endl;
    }
    else if (exception == LINE_NUMBER_ERROR) {
        std::cout << "LINE NUMBER ERROR" << std::endl;
    }
    else {
        std::cout << "SYNTAX ERROR" << std::endl;
    }
}