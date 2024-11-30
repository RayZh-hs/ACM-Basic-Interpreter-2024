//
// Created by Rayzh on 2024/11/30.
//

#include "safeexp.h"

Expression *safeBuildExpr(std::string expr, EvalState& state) {
    if (existDiscreteLetters(expr)) {
        // Things like (a b cd) should not progress forward
        error("DISCRETE LETTERS (Syntax Error)");
    }
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


bool existDiscreteLetters(std::string str) {
    std::smatch buff;
    return std::regex_search(str, buff, Basic::regex_discrete_letters);
}