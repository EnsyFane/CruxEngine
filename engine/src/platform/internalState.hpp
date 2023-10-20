#pragma once

#include "defines.hpp"

#if CPLATFORM_WINDOWS
    #include <Windows.h>
    #include <windowsx.h>
#elif CPLATFORM_LINUX
    #include <xcb/xcb.h>
    #include <X11/keysym.h>
    #include <X11/XKBlib.h> 
    #include <X11/Xlib.h>
    #include <X11/Xlib-xcb.h> 
    #include <sys/time.h>
#endif

typedef struct InternalState {
    #if CPLATFORM_WINDOWS
        HINSTANCE instance;
        HWND handle;
        double clockFrequency;
        LARGE_INTEGER clockStartTime;
    #elif CPLATFORM_LINUX
        Display* display;
        xcb_connection_t* connection;
        xcb_window_t window;
        xcb_screen_t* screen;
        xcb_atom_t wmProtocols;
        xcb_atom_t wmDeleteWindow;
    #endif
} InternalState;
