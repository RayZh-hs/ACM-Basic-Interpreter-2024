/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface, which is an excellent model for
 * the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h

#include <string>
#include <sstream>
#include <utility>
#include "evalstate.hpp"
#include "exp.hpp"
#include "Utils/tokenScanner.hpp"
#include "program.hpp"
#include "parser.hpp"
#include "Utils/error.hpp"
#include "Utils/strlib.hpp"
#include "constants.hpp"
#include "safeexp.h"

class Program;

/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */

class Statement {
public:
    /*
     * Constructor: Statement
     * ----------------------
     * The base class constructor is empty.  Each subclass must provide
     * its own constructor.
     */

    Statement();

    /*
     * Destructor: ~Statement
     * Usage: delete stmt;
     * -------------------
     * The destructor deallocates the storage for this expression.
     * It must be declared virtual to ensure that the correct subclass
     * destructor is called when deleting a statement.
     */

    virtual ~Statement();

    /*
     * Method: execute
     * Usage: stmt->execute(state);
     * ----------------------------
     * This method executes a BASIC statement.  Each of the subclasses
     * defines its own execute method that implements the necessary
     * operations.  As was true for the expression evaluator, this
     * method takes an EvalState object for looking up variables or
     * controlling the operation of the interpreter.
     */

    virtual void execute(EvalState& state, Program& program) = 0;
};


/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 */

class StatementREM : public Statement {
public:
    StatementREM() = default;
    ~StatementREM() override = default;

    void execute(EvalState& state, Program& program) override;
};

// ?fixed? There may be memory leaks in the following classes due to inserted Expression pointers!

class StatementLET : public Statement {
public:
    StatementLET(std::string var, Expression *expr)
        : var(std::move(var)), expr(expr) {}

    ~StatementLET() override {
        delete expr;
    }

    void execute(EvalState& state, Program& program) override;
private:
    std::string var;
    Expression *expr;
};

class StatementPRINT : public Statement {
public:
    explicit StatementPRINT(Expression *expr)
        : expr(expr) {}

    ~StatementPRINT() override {
        delete expr;
    }

    void execute(EvalState& state, Program& program) override;

private:
    Expression *expr;
};

class StatementINPUT : public Statement {
public:
    explicit StatementINPUT(std::string var)
        : var(std::move(var)) {}

    ~StatementINPUT() override = default;

    void execute(EvalState& state, Program& program) override;
private:
    std::string var;
};

class StatementGOTO : public Statement {
public:
    explicit StatementGOTO(const int line_number)
        : line_number(line_number) {}

    ~StatementGOTO() override = default;

    void execute(EvalState& state, Program& program) override;
private:
    int line_number;
};

class StatementIF : public Statement {
public:
    explicit StatementIF(Expression *expr1, const char comparer, Expression *expr2, int line_number)
        : expr1(expr1), expr2(expr2), comparer(comparer), line_number(line_number) {}

    ~StatementIF() override {
        delete expr1;
        delete expr2;
    }

    void execute(EvalState& state, Program& program) override;
private:
    Expression *expr1, *expr2;
    char comparer;
    int line_number;
};

class StatementEND : public Statement {
public:
    StatementEND() = default;

    ~StatementEND() override = default;

    void execute(EvalState& state, Program& program) override;
};

#endif
