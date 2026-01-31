#ifndef LOGGER_H // Only define if not already included (prevents double inclusion)
#define LOGGER_H

#include <string>

// Simple logging functions

void logError(const std::string& message, int line=-1);
void logWarning(const std::string& message, int line=-1);
void logDebug(const std::string& message);


#endif