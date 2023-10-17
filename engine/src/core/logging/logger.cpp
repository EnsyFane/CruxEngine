#include "logger.hpp"
#include "platform/platform.hpp"

#include <ctime>

// TODO: temporary
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

bool Logger::InitializeLogging() {
    // TODO: create log file.
    return true;
}

void Logger::StopLogger() {
    // TODO: cleanup logging/write queued entries.
}

void Logger::LogMessage(LogLevel level, const char* file, int line, const char* message, ...) {
    time_t now;
    time(&now);
    char isoTime[sizeof "2000-02-26T00:00:00Z"];
    strftime(isoTime, sizeof isoTime, "%Y-%m-%dT%H:%M:%SZ", gmtime(&now));

    // HACK: Limits log message to 32,000 characters. Increase if necessary.
    const int messageLength = 32000;
    char originalMessage[messageLength] = {0};

    __builtin_va_list arg_ptr;
    va_start(arg_ptr, message);
    vsnprintf(originalMessage, messageLength, message, arg_ptr);
    va_end(arg_ptr);

    char finalMessage[messageLength];
    sprintf(finalMessage, "%s | [%s]\t| %s | %s:%d\n", isoTime, _logLevelStrings[level], originalMessage, file, line);

    auto isError = level < LOG_LEVEL_WARN;
    if (isError) {
        Platform::ConsoleWriteError(finalMessage, level);
    } else {
        Platform::ConsoleWrite(finalMessage, level);
    }
}
