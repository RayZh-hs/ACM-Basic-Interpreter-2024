/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include "program.hpp"



Program::Program() = default;

Program::~Program() {
    clear();
}

//?fixed? The clear function may lead to memory leak!

void Program::clear() {
    // Replace this stub with your own code
    for (auto cur: line_numbers) {
        delete parsed_program[cur];
    }
    line_numbers.clear();
    literal_program.clear();
    parsed_program.clear();
}

void Program::insertLine(int lineNumber, const std::string &line, Statement *statement) {
    // Replace this stub with your own code
    // Remove the old one if it exists
    removeLine(lineNumber);
    // Insert the new line if !line.empty()
    if (line.empty()) {
        return;
    }
    line_numbers.insert(lineNumber);
    literal_program[lineNumber] = line;
    parsed_program [lineNumber] = statement;
}

void Program::removeLine(int lineNumber) {
    // Replace this stub with your own code
    if (hasLine(lineNumber)) {
        // The line already exists
        // Remove the old line number
        line_numbers.erase(line_numbers.find(lineNumber));
        literal_program.erase(literal_program.find(lineNumber));
        // Automatically free the memory of the Statement
        auto found_statement = parsed_program.find(lineNumber);
        delete found_statement->second;
        parsed_program.erase(found_statement);
    }
}

std::string Program::getLiteral(int lineNumber) {
    // Replace this stub with your own code
    if (hasLine(lineNumber)) {
        return literal_program[lineNumber];
    }
    return "";
}

//void Program::removeLine(int lineNumber) {

Statement *Program::getParsed(int lineNumber) {
   // Replace this stub with your own code
   if (hasLine(lineNumber)) {
       return parsed_program[lineNumber];
   }
    return nullptr;
}

int Program::getFirstLineNumber() {
    // Replace this stub with your own code
    if (line_numbers.empty()) {
        return -1;
    }
    return *line_numbers.begin();
}

int Program::getNextLineNumber(int lineNumber) {
    // Replace this stub with your own code
    auto iter = line_numbers.lower_bound(lineNumber + 1);
    if (iter == line_numbers.end()) {
        return -1;
    }
    return *iter;
}

//more func to add
//todo

bool Program::hasLine(int lineNumber) {
    return line_numbers.count(lineNumber);
}

int Program::getRunningAtLineNumber() const {
    return running_at_line_number;
}

int Program::setRunningAtLineNumber(const int to) {
    return running_at_line_number = to;
}

void Program::run(EvalState &state) {
    running_at_line_number = getFirstLineNumber();
    while (running_at_line_number != -1) {
        parsed_program[running_at_line_number]->execute(state, *this);
        if (!inhibit_pc_flag)
            running_at_line_number = getNextLineNumber(running_at_line_number);
        inhibit_pc_flag = false;    // The flag needs to be reset every round.
    }
}

void Program::list() {
    try {
        for (auto cur: line_numbers) {
            std::cout << literal_program[cur] << std::endl;
        }
    }
    catch (...) {
        error("INTERNAL ERROR");
    }
}

void Program::inhibitPC() {
    inhibit_pc_flag = true;
}
