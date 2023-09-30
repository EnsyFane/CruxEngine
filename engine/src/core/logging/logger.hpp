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
    void LogMessage(LogLevel level, const char* message, ...) const;
    const char* _logLevelStrings[6] = {"FATAL", "ERROR", "WARN", "INFO", "DEBUG", "TRACE"};

public:
    b8 InitializeLogging();
    void StopLogger();

    template<typename... Args> 
    void LogFatal(const char* message, Args... args) {
        LogMessage(LOG_LEVEL_FATAL, message, args...);
    }

    template<typename... Args> 
    void LogError(const char* message, Args... args) {
        LogMessage(LOG_LEVEL_ERROR, message, args...);
    }

#if ENABLE_LOG_WARN == 1
    template<typename... Args> 
    void LogWarning(const char* message, Args... args) {
        LogMessage(LOG_LEVEL_WARN, message, args...);
    }
#else
    template<typename... Args> 
    void LogWarning(const char* message, Args... args) {}
#endif

#if ENABLE_LOG_INFO == 1
    template<typename... Args> 
    void LogInformation(const char* message, Args... args) {
        LogMessage(LOG_LEVEL_INFO, message, args...);
    }
#else
    template<typename... Args> 
    void LogInformation(const char* message, Args... args) { }
#endif

#if ENABLE_LOG_DEBUG == 1
    template<typename... Args> 
    void LogDebug(const char* message, Args... args) {
        LogMessage(LOG_LEVEL_DEBUG, message, args...);
    }
#else
    template<typename... Args> 
    void LogDebug(const char* message, Args... args) { }
#endif

#if ENABLE_LOG_TRACE == 1
    template<typename... Args> 
    void LogTrace(const char* message, Args... args) {
        LogMessage(LOG_LEVEL_TRACE, message, args...);
    }
#else
    template<typename... Args> 
    void LogTrace(const char* message, Args... args) { }
#endif
};
