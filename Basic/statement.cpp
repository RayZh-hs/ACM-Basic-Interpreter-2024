/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include "statement.hpp"


/* Implementation of the Statement class */

int stringToInt(std::string str);

Statement::Statement() = default;

Statement::~Statement() = default;

//todo

void StatementREM::execute(EvalState& state, Program& program) {
  // It is merely a comment, so executing it does nothing.
}

void StatementLET::execute(EvalState& state, Program& program) {
    // try {
        int new_value = expr->eval(state);
        state.setValue(var,
            new_value
        );
    // }
    /*
    catch (ErrorException &exception) {
        if (exception.getMessage() == "VARIABLE NOT DEFINED")
            braise(Basic::VARIABLE_NOT_DEFINED);
        else
            braise(Basic::SYNTAX_ERROR);
        // This ensures that the interpreter can be informed of the exception and can thus halt.
        error("HALT");
    }
    catch (...) {
        braise(Basic::SYNTAX_ERROR);
        // What is wrong here ?
        std::cerr << "Internal Error Occurred" << '\n';
        error("HALT");
    }
    */
    // catch (ErrorException &exception) {
    //     error("VARIABLE NOT DEFINED");
    // }
}

void StatementPRINT::execute(EvalState& state, Program& program) {
    std::cout << expr->eval(state) << std::endl;
}

void StatementINPUT::execute(EvalState& state, Program& program) {
    std::string buff;
    while (true) {
        std::cout << " ? ";
        // std::cin >> buff;
        std::getline(std::cin, buff);
        if (std::cin.eof()) {
            error("QUIT");
        }
        if (matchRegex(buff, Basic::regex_valid_number)) {
            break;
        }
        std::cout << "INVALID NUMBER" << std::endl;
    }
    int set_to = stringToInteger(buff);
    state.setValue(var, set_to);
}

void StatementGOTO::execute(EvalState& state, Program& program) {
    if (!program.hasLine(line_number)) {
        // Basic::braise(Basic::LINE_NUMBER_ERROR);
        error("LINE NUMBER ERROR");
    }
    if (program.getRunningAtLineNumber() == Basic::null_line_number) {
        std::cerr << "Internal Error Occurred at statement.cpp/83" << '\n';
        error("INTERNAL ERROR");
    }
    program.inhibitPC();
    program.setRunningAtLineNumber(line_number);
}

void StatementIF::execute(EvalState& state, Program& program) {
    try {
        int left  = expr1->eval(state);
        int right = expr2->eval(state);
        if (
            (comparer == '=' && left != right) ||
            (comparer == '<' && left >= right) ||
            (comparer == '>' && left <= right)
            ) {
            return;
        }
        // It is here that the program checks whether the line number is within range!
        if (!program.hasLine(line_number)) {
            error("LINE NUMBER NOT FOUND");
            // Forward to catch !
        }
        program.inhibitPC();
        program.setRunningAtLineNumber(line_number);
    }
    catch (ErrorException &exception) {
        if (exception.getMessage() == "LINE NUMBER NOT FOUND")
            error("LINE NUMBER ERROR");
        else
            throw;
    }
}

void StatementEND::execute(EvalState& state, Program& program) {
    program.inhibitPC();
    program.setRunningAtLineNumber(-1);
}
