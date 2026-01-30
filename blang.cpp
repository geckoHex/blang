#include <iostream> // Standard output utilities
#include <fstream>  // Reading file stream
#include <sstream>  // Allows treating strings as streams
#include <vector>   // Dynamic sized list
#include <string>   // String

bool readAndParseFile(std::vector<std::string>& v, std::string inputFileName) {
    // Open the file
    std::ifstream file(inputFileName);

    // Ensure the file was read
    if (!file) {
        std::cerr << "Error: Failed to read input file." << '\n';
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

    // Parse file contents by semicolons 
    while (std::getline(ss, part, ';')) { // Reads from ss, stopping at ';'
        v.push_back(part); // Stores the part before ';' in a string in the vector
    }

    // Function worked and nothing went wrong
    return true;
}

int main(int argc, char* argv[]) { // Argument count, argument values (C string array)
    // Check the correct number of arguments was provided
    if (argc==1) { // Only one argument provided (exec name)
        std::cerr << "Error: No input file provided." << '\n';
        return 1;
    } else if (argc>2) { // Three or more arguments given (exec name, file name, other arg(s))
        std::clog << "Warning: Multiple arguments provided. Dropping additional arguments." << '\n';
    }

    // Read the input file & check success
    std::vector<std::string> instructions; // Initialize vector for the file's instructions
    bool didReadInput = readAndParseFile(instructions, argv[1]); // Pass vector reference and filename argument
    if (!didReadInput) {
        return 1; // Fail the program if input wasn't read
    }

    // Use the result
    int commandCounter = 0; // Initialize counter
    for (const auto& i : instructions) { // Loops over every part in the vector (without copying or modifying)
        commandCounter++; // Increment counter
        std::cout << "Command #" << commandCounter << ") " << i << '\n'; // Fancy print the instruction
    }

    return 0; // Return success
}
