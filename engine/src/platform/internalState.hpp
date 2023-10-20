#pragma once

#include "defines.hpp"

#if CPLATFORM_WINDOWS
    #include <Windows.h>
    #include <windowsx.h>
#elif CPLATFORM_LINUX
    #include <xcb/xcb.h>
    #include <X11/keysym.h>
    #include <X11/Xlib.h>
    #include <X11/Xlib.h>
#endif

typedef struct InternalState {
    #if CPLATFORM_WINDOWS
        HINSTANCE instance;
        HWND handle;
    #elif CPLATFORM_LINUX
    #endif
} InternalState;
