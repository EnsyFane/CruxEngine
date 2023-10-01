#include "assertions.hpp"
#include "../logging/logger.hpp"

void ReportAssertionFailure(const char* expression, const char* file, int line) {
    Logger::LogMessage(LOG_LEVEL_FATAL, file, line, "Assertion failed: %s.", expression);
}

void ReportAssertionFailure(const char* expression, const char* message, const char* file, int line) {
    Logger::LogMessage(LOG_LEVEL_FATAL, file, line, "Assertion failed: %s. Message: %s", expression, message);
}
