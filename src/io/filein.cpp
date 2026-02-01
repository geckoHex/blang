#include "filein.h"
#include "../util/logger.h"

#include <string>
#include <vector>
#include <fstream>  // Reading file stream
#include <sstream>  // Allows treating strings as streams

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