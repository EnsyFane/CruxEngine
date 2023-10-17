#pragma once

#include "defines.hpp"

#if CPLATFORM_WINDOWS
    #include <Windows.h>
    #include <windowsx.h>
#elif CPLATFORM_LINUX
#endif

typedef struct InternalState {
    #if CPLATFORM_WINDOWS
        HINSTANCE instance;
        HWND handle;
    #elif CPLATFORM_LINUX
    #endif
} InternalState;
