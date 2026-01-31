#include <iostream> // Standard output utilities
#include <fstream>  // Reading file stream
#include <sstream>  // Allows treating strings as streams
#include <vector>   // Dynamic sized list
#include <string>   // String

#include "util/logger.h"

bool readAndParseFile(std::vector<std::string>& v, std::string inputFileName) {
    // Open the file
    std::ifstream file(inputFileName);

    // Ensure the file was read
    if (!file) {
        logError("Failed to read input file.");
        return false;
    }

    // Creates a string stream (like a string that can be written to)
    std::stringstream buffer;

    // Copies the file contents to the buffer we made
    buffer << file.rdbuf();

    // Create a string with the whole file contents
    std::string content = buffer.str();

    // Wraps the string in a stream for piece by pice reading (but from memory)
    std::stringstream ss(content);

    // Temporary string to store the part being read
    std::string part;

    // Parse file contents by newlines 
    while (std::getline(ss, part, '\n')) { // Reads from ss, stopping at a newline
        v.push_back(part); // Stores the part before the newline in a string in the vector
    }

    // Function worked and nothing went wrong
    return true;
}

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
