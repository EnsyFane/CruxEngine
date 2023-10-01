#pragma once

#include "defines.hpp"

#ifndef ENABLE_LOG_WARN
    #define ENABLE_LOG_WARN 1
#endif

#ifndef ENABLE_LOG_INFO
    #define ENABLE_LOG_INFO 1
#endif

#ifdef CREALEASE
    #ifndef ENABLE_LOG_DEBUG
        #define ENABLE_LOG_DEBUG 0
    #endif
    #ifndef ENABLE_LOG_TRACE
        #define ENABLE_LOG_TRACE 0
    #endif
#else
    #ifndef ENABLE_LOG_DEBUG
        #define ENABLE_LOG_DEBUG 1
    #endif
    #ifndef ENABLE_LOG_TRACE
        #define ENABLE_LOG_TRACE 1
    #endif
#endif

typedef enum LogLevel {
    LOG_LEVEL_FATAL,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARN,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_TRACE
} LogLevel;

class CAPI Logger {
private:
    static constexpr const char* _logLevelStrings[6] = {"FATAL", "ERROR", "WARN", "INFO", "DEBUG", "TRACE"};

public:
    static bool InitializeLogging();
    static void StopLogger();
    static void LogMessage(LogLevel level, const char* file, int line, const char* message, ...);

#define LOG_FATAL(message, ...) Logger::LogMessage(LOG_LEVEL_FATAL, __FILE__, __LINE__, message, __VA_ARGS__)
#define LOG_ERROR(message, ...) Logger::LogMessage(LOG_LEVEL_ERROR, __FILE__, __LINE__, message, __VA_ARGS__)

#if ENABLE_LOG_WARN == 1
    #define LOG_WARNING(message, ...) Logger::LogMessage(LOG_LEVEL_WARN, __FILE__, __LINE__, message, __VA_ARGS__)
#else
    #define LOG_WARNING(message, ...)
#endif

#if ENABLE_LOG_INFO == 1
    #define LOG_INFO(message, ...) Logger::LogMessage(LOG_LEVEL_INFO, __FILE__, __LINE__, message, __VA_ARGS__)
#else
    #define LOG_INFO(message, ...)
#endif

#if ENABLE_LOG_DEBUG == 1
    #define LOG_DEBUG(message, ...) Logger::LogMessage(LOG_LEVEL_DEBUG, __FILE__, __LINE__, message, __VA_ARGS__)
#else
    #define LOG_DEBUG(message, ...)
#endif

#if ENABLE_LOG_TRACE == 1
    #define LOG_TRACE(message, ...) Logger::LogMessage(LOG_LEVEL_TRACE, __FILE__, __LINE__, message, __VA_ARGS__)
#else
    #define LOG_TRACE(message, ...)
#endif
};
