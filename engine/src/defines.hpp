#pragma once

// Properly define static assertions.
#if defined(__clang__) || defined(__gcc__)
    #define STATIC_ASSERT _Static_assert
#else
    #define STATIC_ASSERT static_assert
#endif

// Ensure all types are of the correct size.
STATIC_ASSERT(sizeof(unsigned char) == 1, "Expected unsigned char to be 1 byte.");
STATIC_ASSERT(sizeof(unsigned short) == 2, "Expected unsigned short to be 2 bytes.");
STATIC_ASSERT(sizeof(unsigned int) == 4, "Expected unsigned int to be 4 bytes.");
STATIC_ASSERT(sizeof(unsigned long long) == 8, "Expected unsigned long long to be 8 bytes.");

STATIC_ASSERT(sizeof(signed char) == 1, "Expected signed char to be 1 byte.");
STATIC_ASSERT(sizeof(signed short) == 2, "Expected signed short to be 2 bytes.");
STATIC_ASSERT(sizeof(signed int) == 4, "Expected signed int to be 4 bytes.");
STATIC_ASSERT(sizeof(signed long long) == 8, "Expected signed long long to be 8 bytes.");

STATIC_ASSERT(sizeof(float) == 4, "Expected float to be 4 bytes.");
STATIC_ASSERT(sizeof(double) == 8, "Expected double to be 8 bytes.");

// Platform detection
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) 
    #define CPLATFORM_WINDOWS 1
    #ifndef _WIN64
        #error "64-bit is required on Windows!"
    #endif
#elif defined(__linux__) || defined(__gnu_linux__)
// Linux OS
    #define CPLATFORM_LINUX 1
    #if defined(__ANDROID__)
        #define CPLATFORM_ANDROID 1
    #endif
#elif defined(__unix__)
    // Catch anything not caught by the above.
    #define CPLATFORM_UNIX 1
#elif defined(_POSIX_VERSION)
    // Posix
    #define CPLATFORM_POSIX 1
#elif __APPLE__
    // Apple platforms
    #define CPLATFORM_APPLE 1
    #include <TargetConditionals.h>

    #if TARGET_IPHONE_SIMULATOR
        // iOS Simulator
        #define CPLATFORM_IOS 1
        #define CPLATFORM_IOS_SIMULATOR 1
    #elif TARGET_OS_IPHONE
        // iOS device
        #define CPLATFORM_IOS 1
    #elif TARGET_OS_MAC
        // Other kinds of Mac OS
    #else
        #error "Unknown Apple platform"
    #endif
#else
    #error "Unknown platform!"
#endif

#ifdef CEXPORT
    // Exports
    #ifdef _MSC_VER
        #define CAPI __declspec(dllexport)
    #else
        #define CAPI __attribute__((visibility("default")))
    #endif
#else
    // Imports
    #ifdef _MSC_VER
        #define CAPI __declspec(dllimport)
    #else
        #define CAPI
    #endif
#endif
