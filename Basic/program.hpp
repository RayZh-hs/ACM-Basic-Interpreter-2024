/*
 * File: program.h
 * ---------------
 * This interface exports a Program class for storing a BASIC
 * program.
 */

#ifndef _program_h
#define _program_h

#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include "statement.hpp"
#include "errorReporter.hpp"


class Statement;

/*
 * This class stores the lines in a BASIC program.  Each line
 * in the program is stored in order according to its line number.
 * Moreover, each line in the program is associated with two
 * components:
 *
 * 1. The source line, which is the complete line (including the
 *    line number) that was entered by the user.
 *
 * 2. The parsed representation of that statement, which is a
 *    pointer to a Statement.
 */

class Program {

public:

/*
 * Constructor: Program
 * Usage: Program program;
 * -----------------------
 * Constructs an empty BASIC program.
 */
    Program();

/*
 * Destructor: ~Program
 * Usage: usually implicit
 * -----------------------
 * Frees any heap storage associated with the program.
 */
    ~Program();

/*
 * Method: clear
 * Usage: program.clear();
 * -----------------------
 * Removes all lines from the program.
 */
    void clear();

/*
 * Method: insertSourceLine
 * Usage: program.insertSourceLine(lineNumber, line, statement);
 * -----------------------------------------------
 * Adds a source line to the program with the specified line number.
 * If that line already exists, the text of the line replaces
 * the text of any existing line and the parsed representation
 * (if any) is deleted.  If the line is new, it is added to the
 * program in the correct sequence. This should not be called to
 * remove a line; use removeLine(lineNumber) instead.
 */
    void insertLine(int lineNumber, const std::string& line, Statement *statement);

/*
 * Method: removeLine
 * Usage: program.removeLine(lineNumber);
 * --------------------------------------------
 * Removes the line with the specified number from the program,
 * freeing the memory associated with any parsed representation.
 * If no such line exists, this method simply returns without
 * performing any action.
 */
    void removeLine(int lineNumber);

/*
 * Method: getLiteral
 * Usage: string line = program.getLiteral(lineNumber);
 * -------------------------------------------------------
 * Returns the program line with the specified line number.
 * If no such line exists, this method returns the empty string.
 */
    std::string getLiteral(int lineNumber);

/*
 * Method: getParsed
 * Usage: Statement *stmt = program.getParsed(lineNumber);
 * ----------------------------------------------------------------
 * Retrieves the parsed representation of the statement at the
 * specified line number.  If no value has been set, this method
 * returns NULL.
 */
    Statement *getParsed(int lineNumber);

/*
 * Method: getFirstLineNumber
 * Usage: int lineNumber = program.getFirstLineNumber();
 * -----------------------------------------------------
 * Returns the line number of the first line in the program.
 * If the program has no lines, this method returns -1.
 */

    int getFirstLineNumber();

/*
 * Method: getNextLineNumber
 * Usage: int nextLine = program.getNextLineNumber(lineNumber);
 * ------------------------------------------------------------
 * Returns the line number of the first line in the program whose
 * number is larger than the specified one, which must already exist
 * in the program.  If no more lines remain, this method returns -1.
 */

    int getNextLineNumber(int lineNumber);

    //more func to add
    //todo

    bool hasLine(int lineNumber);

    int getRunningAtLineNumber() const ;
    int setRunningAtLineNumber(int to);

private:

    // Fill this in with whatever types and instance variables you need
    //todo

    // The collection of all the line numbers in this program.
    std::set<int> line_numbers;

    // The user input, stored in this unordered map literally.
    std::unordered_map<int, std::string> literal_program;
    // The parsed version of user input lines, called using the virtual exec() method.
    std::unordered_map<int, Statement*>  parsed_program;

    int running_at_line_number = Basic::null_line_number;

};

#endif
