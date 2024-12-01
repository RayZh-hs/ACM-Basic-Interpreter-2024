/*
 * File: Basic.cpp
 * ---------------
 * This file is the starter project for the BASIC interpreter.
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.hpp"
#include "parser.hpp"
#include "program.hpp"
#include "Utils/error.hpp"
#include "Utils/tokenScanner.hpp"
#include "Utils/strlib.hpp"
#include <regex>


/* Function prototypes */

// Process a line (and execute it if needs be).
void processLine(std::string line, Program &program, EvalState &state);
// You must ensure that such a number does indeed exist!
int getLeadingNumber(const std::string &line);
// Identify whether a string is a valid variable name.
bool isValidVariableName(const std::string &str);

/* Main program */

int main() {
    EvalState state;
    Program program;
    //cout << "Stub implementation of BASIC" << endl;
    while (true) {
        try {
            std::string input;
            getline(std::cin, input);
            if (std::cin.eof()) {
                error("QUIT");
            }
            if (input.empty())
                continue;
            processLine(input, program, state);
        } catch (ErrorException &ex) {
            const std::string msg = ex.getMessage();
            if (msg == "QUIT") {
                // Break out of the loop instead of calling exit(0) ensures that the destructors can be called
                break;
            }
            if (
                msg == "Illegal term in expression"
            ||  msg == "Unbalanced parentheses in expression"
            || (msg.length() > 22 && msg.substr(0, 21) == "parseExp: Found extra")
            ) {
                std::cout << "SYNTAX ERROR" << std::endl;
                continue;
            }
            std::cout << ex.getMessage() << std::endl;
        }
    }
    return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version of
 * implementation, the program reads a line, parses it as an expression,
 * and then prints the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */
void processLine(std::string line, Program &program, EvalState &state) {
    // TokenScanner scanner;
    // scanner.ignoreWhitespace();
    // scanner.scanNumbers();
    // scanner.setInput(line);

    //todo
    line = trim(line);
    //: [num] REM [msg]
    if (matchRegex(line, Basic::regex_sav_rem)) {
        int num = getLeadingNumber(line);
        auto stat = new StatementREM();
        program.insertLine(num, line, stat);
    }
    //: [num] LET [var] = [expr]
    else if (matchRegex(line, Basic::regex_sav_let)) {
        const int num = getLeadingNumber(line);
        const auto group = groupRegex(line, Basic::regex_sav_let);
        const std::string var = trim(group[2]);
        if (!isValidVariableName(var)) {
            error("SYNTAX ERROR");
        }
        const std::string expr_string = trim(group[3]);
        // try parsing the expression
        auto expr = safeBuildExpr(expr_string);
        auto stat = new StatementLET(var, expr);
        program.insertLine(num, line, stat);
    }
    //: [num] PRINT [expr]
    else if (matchRegex(line, Basic::regex_sav_print)) {
        const int num = getLeadingNumber(line);
        const auto group = groupRegex(line, Basic::regex_sav_print);
        const std::string expr_string = trim(group[2]);
        // try parsing the expression
        auto expr = safeBuildExpr(expr_string);
        auto stat = new StatementPRINT(expr);
        program.insertLine(num, line, stat);
    }
    //: [num] INPUT [var]
    else if (matchRegex(line, Basic::regex_sav_input)) {
        const int num = getLeadingNumber(line);
        const auto group = groupRegex(line, Basic::regex_sav_input);
        const std::string var = trim(group[2]);
        if (!isValidVariableName(var)) {
            error("SYNTAX ERROR");
        }
        auto stat = new StatementINPUT(var);
        program.insertLine(num, line, stat);
    }
    //: [num] GOTO [line_number]
    else if (matchRegex(line, Basic::regex_sav_goto)) {
        const int num = getLeadingNumber(line);
        const auto group = groupRegex(line, Basic::regex_sav_goto);
        const int line_number = stringToInteger(group[2]);
        auto stat = new StatementGOTO(line_number);
        program.insertLine(num, line, stat);
    }
    //: [num] IF [expr1] [cmp] [expr2] THEN [line_number]
    else if (matchRegex(line, Basic::regex_sav_if)) {
        const int num = getLeadingNumber(line);
        const auto group = groupRegex(line, Basic::regex_sav_if);
        const std::string expr1_string = trim(group[2]);
        const char        cmp          = trim(group[3])[0];
        const std::string expr2_string = trim(group[4]);
        const int         line_number  = stringToInteger(trim(group[5]));
        if (cmp != '<' && cmp != '=' && cmp != '>') {
            error("SYNTAX ERROR");
        }
        Expression *expr1 = safeBuildExpr(expr1_string);
        Expression *expr2 = safeBuildExpr(expr2_string);
        auto stat = new StatementIF(expr1, cmp, expr2, line_number);
        program.insertLine(num, line, stat);
    }
    //: [num] END
    else if (matchRegex(line, Basic::regex_sav_end)) {
        int num = getLeadingNumber(line);
        auto stat = new StatementEND();
        program.insertLine(num, line, stat);
    }
    //: [num]
    else if (matchRegex(line, Basic::regex_sav_del)) {
        // Note that this does nothing if the line does not exist
        const int num = getLeadingNumber(line);
        program.removeLine(num);
    }
    //: LET [var] = [expr]
    else if (matchRegex(line, Basic::regex_exe_let)) {
        const auto group = groupRegex(line, Basic::regex_exe_let);
        const std::string var = trim(group[1]);
        if (!isValidVariableName(var)) {
            error("SYNTAX ERROR");
        }
        const std::string expr_string = trim(group[2]);
        // try parsing the expression
        auto expr = safeBuildExpr(expr_string);
        auto stat = StatementLET(var, expr);
        stat.execute(state, program);
    }
    //: PRINT [expr]
    else if (matchRegex(line, Basic::regex_exe_print)) {
        const auto group = groupRegex(line, Basic::regex_exe_print);
        const std::string expr_string = trim(group[1]);
        // try parsing the expression
        auto expr = safeBuildExpr(expr_string);
        auto stat = StatementPRINT(expr);
        stat.execute(state, program);
    }
    //: INPUT [var]
    else if (matchRegex(line, Basic::regex_exe_input)) {
        const auto group = groupRegex(line, Basic::regex_exe_input);
        const std::string var = trim(group[1]);
        if (!isValidVariableName(var)) {
            error("SYNTAX ERROR");
        }
        auto stat = StatementINPUT(var);
        stat.execute(state, program);
    }
    //: RUN
    else if (matchRegex(line, Basic::regex_exe_run)) {
        // Execute the program directly
        program.run(state);
    }
    //: LIST
    else if (matchRegex(line, Basic::regex_exe_list)) {
        // List the programs in the buff
        program.list();
    }
    //: CLEAR
    else if (matchRegex(line, Basic::regex_exe_clear)) {
        // Clear the program
        program.clear();
        state.Clear();
    }
    //: QUIT
    else if (matchRegex(line, Basic::regex_exe_quit)) {
        // Throw a QUIT exception to quit the software
        error("QUIT");
    }
    //: HELP
    else if (matchRegex(line, Basic::regex_exe_help)) {
        std::cout << "\n" << Basic::help_msg << "\n";
    }
    //: everything else is a SYNTAX ERROR
    else {
        error("SYNTAX ERROR");
    }
}

int getLeadingNumber(const std::string &line) {
    std::smatch result;
    if (!std::regex_search(line, result, Basic::regex_leading_number)) {
        error("INTERNAL ERROR");
        return -1;
    }
    return stringToInteger(result.str());
}

bool isValidVariableName(const std::string &str) {
    return (
        matchRegex(str, Basic::regex_valid_variable_mode)
    && !matchRegex(str, Basic::regex_reserved_names)
    );
}