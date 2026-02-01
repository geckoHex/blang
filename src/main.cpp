#include <iostream> // Standard output utilities
#include <vector>   // Dynamic sized list
#include <string>   // String

#include "util/logger.h"
#include "io/file_in.h"

bool runCommand(const std::string& command, int lineNumber) {
    // Get the indexes of the open and closed parentheses
    size_t openPos = command.find('('); // Assign an unsigned integer (used for indexes in C++) to the index where the open parentheses appears
    size_t closePos = command.find(')'); // Same as above but for closing parentheses

    // Validate the line's parentheses syntax
    if (openPos==std::string::npos) { // If the value of the first parenthes is npos (used to indicate failure of string seeking)
        logError("Missing opening parentheses.", lineNumber);
        return false;
    } else if (closePos==std::string::npos) {
        logError("Missing closing parentheses.", lineNumber);
        return false;
    } else if (closePos<openPos) {
        logError("Opening parentheses appears before closing parentheses.", lineNumber);
        return false;
    }

    // Validate a command (token) is given by checking the open parentheses is not the first char in the line
    if (openPos==0) {
        logError("No command is given before the opening parentheses.", lineNumber);
        return false;
    }

    // Get the command token
    std::string token = command.substr(0, openPos);

    logDebug("Command is to do the action of " + token); 
    return true;
}

int main(int argc, char* argv[]) { // Argument count, argument values (C string array)
    // Check the correct number of arguments was provided
    if (argc==1) { // Only one argument provided (exec name)
        logError("No input file is provided.");
        return 1;
    } else if (argc>2) { // Three or more arguments given (exec name, file name, other arg(s))
        logWarning("Too many program arguments provided. Dropping additional arguments.");
    }

    // Read the input file & check success
    std::vector<std::string> instructions; // Initialize vector for the file's instructions
    bool didReadInput = readAndParseFile(instructions, argv[1]); // Pass vector reference and filename argument
    if (!didReadInput) {
        return 1; // Fail the program if input wasn't read
    }

    // Use the result
    int commandCounter = 0; // Initialize counter
    bool canRunLine;
    for (const auto& i : instructions) { // Loops over every part in the vector (without copying or modifying)
        commandCounter++; // Increment counter
        canRunLine = runCommand(i, commandCounter);
        if (!canRunLine) {
            return 1; // Fail
        }
    }

    return 0; // Return success
}
