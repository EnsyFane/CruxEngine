#include "platform/platform.hpp"

#if CPLATFORM_WINDOWS

#include "core/logging/logger.hpp"

#include <Windows.h>
#include <windowsx.h>
#include <stdlib.h>

LRESULT CALLBACK Win32ProcessMessage(HWND handle, unsigned int message, WPARAM wParam, LPARAM lParam);
void WriteToConsole(HANDLE consoleHandle, const char* message, const LogLevel color);

bool Platform::Initialize(const char* aplicationName, const int x, const int y, const int width, const int height) {
    this->_state = (InternalState*)malloc(sizeof(InternalState));
    this->_state->instance = GetModuleHandle(0);

    auto icon = LoadIcon(this->_state->instance, IDI_APPLICATION);
    WNDCLASSA wc;
    memset(&wc, 0, sizeof(wc));
    wc.style = CS_DBLCLKS;
    wc.lpfnWndProc = Win32ProcessMessage;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = this->_state->instance;
    wc.hIcon = icon;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL;
    wc.lpszClassName = "crux_window_class";

    if (!RegisterClassA(&wc)) {
        MessageBoxA(0, "Window registration failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }

    auto clientX = x;
    auto clientY = y;
    auto clientWidth = width;
    auto clientHeight = height;

    auto windowX = clientX;
    auto windowY = clientY;
    auto windowWidth = clientWidth;
    auto windowHeight = clientHeight;

    auto windowStyle = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;
    auto windowStyleEx = WS_EX_APPWINDOW;

    windowStyle |= WS_MAXIMIZEBOX;
    windowStyle |= WS_MINIMIZEBOX;
    windowStyle |= WS_THICKFRAME;

    RECT borderRect = {0, 0, 0, 0};
    AdjustWindowRectEx(&borderRect, windowStyle, 0, windowStyleEx); 

    windowX += borderRect.left;
    windowY += borderRect.top;

    windowWidth += borderRect.right - borderRect.left;
    windowHeight += borderRect.bottom - borderRect.top;

    auto handle = CreateWindowExA(
        windowStyleEx,
        wc.lpszClassName,
        aplicationName,
        windowStyle,
        windowX,
        windowY,
        windowWidth,
        windowHeight,
        0,
        0,
        this->_state->instance,
        0);

    if (handle == 0) {
        MessageBoxA(0, "Window creation failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);

        LOG_FATAL("Window creation failed!");
        return false;
    }

    this->_state->handle = handle;

    bool shouldAcceptInput = true; // TODO: Make this a parameter.
    auto showWindowCommand = shouldAcceptInput ? SW_SHOW : SW_SHOWNOACTIVATE;

    ShowWindow(this->_state->handle, showWindowCommand);

    LARGE_INTEGER clockFrequency;
    QueryPerformanceFrequency(&clockFrequency);
    _clockFrequency = 1.0 / (double)clockFrequency.QuadPart;
    QueryPerformanceCounter(&_clockStartTime);

    return true;
}

void Platform::Stop() {
    if (this->_state->handle) {
        DestroyWindow(this->_state->handle);
        this->_state->handle = 0;
    }
}

bool Platform::PumpMessages() {
    MSG message;
    while (PeekMessageA(&message, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&message);
        DispatchMessageA(&message);
    }

    return true;
}

void* Platform::Allocate(const long long int size, const bool aligned) {
    return malloc(size);
}

void Platform::Free(void* block, const bool aligned) {
    free(block);
}

void* Platform::MemoryCopy(void* destination, const void* source, const unsigned long int size) {
    return memcpy(destination, source, size);
}

void* Platform::MemorySet(void* destination, int value, const unsigned long long int size) {
    return memset(destination, value, size);
}

void Platform::ConsoleWrite(const char* message, const LogLevel level) {
    auto consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    WriteToConsole(consoleHandle, message, level);
}

void Platform::ConsoleWriteError(const char* message, const LogLevel level) {
    auto consoleHandle = GetStdHandle(STD_ERROR_HANDLE);
    WriteToConsole(consoleHandle, message, level);
}

double Platform::GetTime() const {
    LARGE_INTEGER currentTime;
    QueryPerformanceCounter(&currentTime);
    return (double)currentTime.QuadPart * _clockFrequency;
}

void Platform::PSleep(const unsigned long long int milliseconds) const {
    Sleep(milliseconds);
}

LRESULT CALLBACK Win32ProcessMessage(HWND handle, unsigned int message, WPARAM wParam, LPARAM lParam) {
    // TODO: Extract into methods
    switch (message) {
        case WM_ERASEBKGND: {
            return 1;
        }
        case WM_CLOSE: {
            // TODO: Fire an event here.
            return 0;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }
        case WM_SIZE: {
            // Get the updated size.
            // RECT r;
            // GetClientRect(handle, &r);
            // auto width = r.right - r.left;
            // auto height = r.bottom - r.top;

            // TODO: Fire an event here.
        } break;
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP: {
            // bool pressed = (message == WM_KEYDOWN || message == WM_SYSKEYDOWN);
            // TODO: Input processing.
        } break;
        case WM_MOUSEMOVE: {
            // auto xPosition = GET_X_LPARAM(lParam);
            // auto yPosition = GET_Y_LPARAM(lParam);
            // TODO: Input processing.
        } break;
        case WM_MOUSEWHEEL: {
            // auto delta = GET_WHEEL_DELTA_WPARAM(wParam);
            // if (delta) {
            //     delta = delta < 0 ? -1 : 1;
            //     // TODO: Input processing.
            // }
        } break;
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP: {
            // bool pressed = (message == WM_LBUTTONDOWN || message == WM_RBUTTONDOWN || message == WM_MBUTTONDOWN);
            // TODO: Input processing.
        } break;
    }

    return DefWindowProcA(handle, message, wParam, lParam);
}

static int GetFlagForColor(const LogLevel color)
{
    switch (color)
    {
        case LOG_LEVEL_FATAL:
            return BACKGROUND_RED;
        case LOG_LEVEL_ERROR:
            return FOREGROUND_RED;
        case LOG_LEVEL_WARN:
            return FOREGROUND_RED | FOREGROUND_GREEN;
        case LOG_LEVEL_INFO:
            return FOREGROUND_GREEN;
        case LOG_LEVEL_DEBUG:
            return FOREGROUND_BLUE;
        case LOG_LEVEL_TRACE:
            return FOREGROUND_INTENSITY;
    };
}

void WriteToConsole(HANDLE consoleHandle, const char* message, const LogLevel level) {
    auto color = GetFlagForColor(level);
    SetConsoleTextAttribute(consoleHandle, color);

    OutputDebugStringA(message);
    auto length = strlen(message);
    LPDWORD written = 0;
    WriteConsoleA(consoleHandle, message, (DWORD)length, written, nullptr);
}

#endif
