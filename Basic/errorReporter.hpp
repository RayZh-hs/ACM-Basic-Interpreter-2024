//
// Created by Rayzh on 2024/11/30.
//

#ifndef ERROR_REPORTER_H
#define ERROR_REPORTER_H

#include <iostream>

enum BException {
    DIVIDE_BY_ZERO,
    INVALID_NUMBER,
    VARIABLE_NOT_DEFINED,
    LINE_NUMBER_ERROR,
    SYNTAX_ERROR
};

/**
 * @brief Raise an external exception to the user.
 *
 * @param exception The exception to raise, one of the five defined BException-s.
 */
void braise(BException exception);

#endif //ERROR_REPORTER_H
