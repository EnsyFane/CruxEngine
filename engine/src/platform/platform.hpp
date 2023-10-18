#pragma once

#include "defines.hpp"
#include "internalState.hpp"
#include "../core/logging/logger.hpp"

class CAPI Platform {
private:
    InternalState* _state;
    double _clockFrequency;
    LARGE_INTEGER _clockStartTime;
public:
    bool Initialize(const char* aplicationName, const int x, const int y, const int width, const int height);
    void Stop();
    bool PumpMessages();

    void* Allocate(const long long int size, const bool aligned);
    void Free(void* block, const bool aligned);
    void* MemoryCopy(void* destination, const void* source, const unsigned long int size);
    void* MemorySet(void* destination, const int value, const unsigned long long int size);

    static void ConsoleWrite(const char* message, const LogLevel level);
    static void ConsoleWriteError(const char* message, const LogLevel level);

    double GetTime();

    void PSleep(const unsigned long long int milliseconds); 
};
