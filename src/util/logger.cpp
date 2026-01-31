#include "logger.h"
#include <iostream>

void logError(const std::string& message, int line) {
    std::cerr << "ERROR on line " << line << ": " << message << '\n';
}

void logWarning(const std::string& message, int line) {
    std::clog << "WARNING one line " << line << ": " << message << '\n';
}

void logDebug(const std::string& message) {
    std::clog << "DEBUG: " << message << '\n';
}
