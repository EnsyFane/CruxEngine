#pragma once

#include "defines.hpp"

#ifndef CASSERTIONS_ENABLED
    #define CASSERTIONS_ENABLED 1
#endif

#if CASSERTIONS_ENABLED == 1
    #if _MSC_VER
        #include <intrin.h>
        #define debugBreak() __debugbreak()
    #else
        #define debugBreak() __builtin_trap()
    #endif
    
    CAPI void ReportAssertionFailure(const char* expression, const char* file, int line);
    CAPI void ReportAssertionFailure(const char* expression, const char* message, const char* file, int line);
    
    #define CASSERT(expr)                                       \
    {                                                           \
        if (!(expr)) {                                          \
            ReportAssertionFailure(#expr, __FILE__, __LINE__);  \
            debugBreak();                                       \
        }                                                       \
    }

    #define CASSERT_MESSAGE(expr, message)                                \
    {                                                                     \
        if (!(expr)) {                                                    \
            ReportAssertionFailure(#expr, message, __FILE__, __LINE__);   \
            debugBreak();                                                 \
        }                                                                 \
    }

    #ifdef _DEBUG
        #define CASSERT_DEBUG(expr)                                      \
        {                                                                \
            if (!(expr)) {                                               \
                ReportAssertionFailure(#expr, __FILE__, __LINE__);       \
                debugBreak();                                            \
            }                                                            \
        }
    #else
        #define CASSERT_DEBUG(expr)
    #endif
#else
    #define CASSERT(expr)
    #define CASSERT_MSG(expr, message)
    #define CASSERT_DEBUG(expr)
#endif
