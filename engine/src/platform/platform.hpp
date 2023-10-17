#pragma once

#include "defines.hpp"
#include "internalState.hpp"

class CAPI Platform {
private:
    InternalState* _state;
    double _clockFrequency;
    LARGE_INTEGER _clockStartTime;
public:
    bool Initialize(const char* aplicationName, int x, int y, int width, int height);
    void Stop();
    bool PumpMessages();

    void* Allocate(long long int size, bool aligned);
    void Free(void* block, bool aligned);
    void* MemoryZero(void* block, unsigned long long int size);
    void* MemoryCopy(void* destination, const void* source, unsigned long int size);
    void* MemorySet(void* destination, int value, unsigned long long int size);

    static void ConsoleWrite(const char* message, unsigned char color);
    static void ConsoleWriteError(const char* message, unsigned char color);

    double GetTime();

    void PSleep(unsigned long long int milliseconds); 
};