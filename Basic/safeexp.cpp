//
// Created by Rayzh on 2024/11/30.
//

#include "safeexp.h"

Expression *safeBuildExpr(std::string expr) {
    if (preparseTestFailed(expr)) {
        error("SYNTAX ERROR");
    }
    try {
        // Concentrate `expr`
        expr = removeWhitespace(expr);
        // Prepare for the scan
        TokenScanner parser_token_scanner(expr);
        parser_token_scanner.ignoreWhitespace();
        parser_token_scanner.scanNumbers();
        // Retrieve the parsed expression tree
        Expression *parsed = parseExp(parser_token_scanner);
        // Fetch the value
        // return parsed->eval(state);
        return parsed;
    }
    catch (...) {
        error("SYNTAX ERROR");
        return nullptr;
    }
}


bool preparseTestFailed(std::string str) {
    std::smatch buff;
    return
        // guard against `a b` -> `ab`
        std::regex_search(str, buff, Basic::regex_discrete_letters)

        // guard against `++` `/-` -> UB
    ||  std::regex_search(str, buff, Basic::regex_concentrated_symbols)

        // guard against (a + b)c -> MLE
    ||  std::regex_search(str, buff, Basic::regex_connected_brackets)
;}