#include <iostream> // Standard output utilities
#include <fstream>  // Reading file stream
#include <sstream>  // Allows treating strings as streams
#include <vector>   // Dynamic sized list
#include <string>   // String

int main() {
    
    // Open the file
    std::ifstream file("example/program.blang");

    // Ensure the file was read
    if (!file) {
        std::cerr << "Failed to open file";
    }

    // Creates a string stream (like a string that can be written to)
    std::stringstream buffer;

    // Copies the file contents to the buffer we made
    buffer << file.rdbuf();

    // Create a string with the whole file contents
    std::string content = buffer.str();

    // Initialize the vector (dynamic list) of parts
    std::vector<std::string> parts;

    // Wraps the string in a stream for piece by pice reading (but from memory)
    std::stringstream ss(content);

    // Temporary string to store the part being read
    std::string part;

    // Parse file contents by semicolons 
    while (std::getline(ss, part, ';')) { // Reads from ss, stopping at ';'
        parts.push_back(part); // Stores the part before ';' in a string in the vector
    }

    // Use the result
    int instruction = 0; // Initialize counter
    for (const auto& p : parts) { // Loops over every part in the vector (without copying or modifying)
        instruction++; // Increment counter
        std::cout << "Instruction #" << instruction << ") " << p << '\n'; // Fancy print the instruction
    }

    return 0; // Return success
}
