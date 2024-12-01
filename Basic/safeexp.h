//
// Created by Rayzh on 2024/11/30.
//

#ifndef SAFEEXP_H
#define SAFEEXP_H

#include <string>
#include "evalstate.hpp"
#include <regex>
#include "constants.hpp"
#include "Utils/tokenScanner.hpp"
#include "Utils/strlib.hpp"
#include "exp.hpp"
#include "parser.hpp"

/**
* @brief Evaluates a string and returns the value safely. Any anomaly spotted, it will raise an exception.
*/
Expression *safeBuildExpr(std::string exp);

bool existDiscreteLetters (std::string str);


#endif //SAFEEXP_H
