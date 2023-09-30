#include "logger.hpp"
#include <ctime>

// TODO: temporary
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

void Logger::LogMessage(LogLevel level, const char* message, ...) const {
    time_t now;
    time(&now);
    char isoTime[sizeof "2000-02-26T00:00:00Z"];
    strftime(isoTime, sizeof isoTime, "%Y-%m-%dT%H:%M:%SZ", gmtime(&now));

    // HACK: Limits log message to 32,000 characters. Increase if necessary.
    char originalMessage[32000] = {0};

    __builtin_va_list arg_ptr;
    va_start(arg_ptr, message);
    vsnprintf(originalMessage, 32000, message, arg_ptr);
    va_end(arg_ptr);

    char finalMessage[32000];
    sprintf(finalMessage, "%s | [%s]\t| %s", isoTime, _logLevelStrings[level], originalMessage);

    // TODO: platform-specific output.
    printf("%s\n", finalMessage);
}
