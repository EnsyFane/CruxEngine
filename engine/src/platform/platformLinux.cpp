#include "platform.hpp"

#if CPLATFORM_LINUX

#if _POSIX_C_SOURCE >= 199309L
    #include <time.h>
#else
    #include <unistd.h>
#endif

#include "core/logging/logger.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

bool Platform::Initialize(const char* aplicationName, const int x, const int y, const int width, const int height) {
    this->_state = (InternalState*)malloc(sizeof(InternalState));

    this->_state->display = XOpenDisplay(NULL);
    XAutoRepeatOff(this->_state->display);

    this->_state->connection = XGetXCBConnection(this->_state->display);
    if (xcb_connection_has_error(this->_state->connection)) {
        LOG_FATAL("Failed to get xcb connection from display");
        return false;
    }

    const auto setup = xcb_get_setup(this->_state->connection);
    auto screenIterator = xcb_setup_roots_iterator(setup);
    for (int s = 0; s > 0; s--) {
        xcb_screen_next(&screenIterator);
    }
    this->_state->screen = screenIterator.data;

    this->_state->window = xcb_generate_id(this->_state->connection);

    auto eventMask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    unsigned int events = XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE
        | XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE
        | XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_POINTER_MOTION
        | XCB_EVENT_MASK_STRUCTURE_NOTIFY;
    unsigned int valueList[] = { this->_state->screen->black_pixel, events };

    xcb_create_window(
        this->_state->connection,
        XCB_COPY_FROM_PARENT,
        this->_state->window,
        this->_state->screen->root,
        x, y,
        width, height,
        0,
        XCB_WINDOW_CLASS_INPUT_OUTPUT,
        this->_state->screen->root_visual,
        eventMask,
        valueList
    );

    xcb_change_property(
        this->_state->connection,
        XCB_PROP_MODE_REPLACE,
        this->_state->window,
        XCB_ATOM_WM_NAME,
        XCB_ATOM_STRING,
        8,
        strlen(aplicationName),
        aplicationName
    );

    auto wmDeleteCookie = xcb_intern_atom(
        this->_state->connection,
        0,
        strlen("WM_DELETE_WINDOW"),
        "WM_DELETE_WINDOW"
    );
    auto wmProtocolsCookie = xcb_intern_atom(
        this->_state->connection,
        0,
        strlen("WM_PROTOCOLS"),
        "WM_PROTOCOLS"
    );
    auto wmDeleteReply = xcb_intern_atom_reply(
        this->_state->connection,
        wmDeleteCookie,
        NULL
    );
    auto wmProtocolsReply = xcb_intern_atom_reply(
        this->_state->connection,
        wmProtocolsCookie,
        NULL
    );
    this->_state->wmDeleteWindow = wmDeleteReply->atom;
    this->_state->wmProtocols = wmProtocolsReply->atom;

    xcb_change_property(
        this->_state->connection,
        XCB_PROP_MODE_REPLACE,
        this->_state->window,
        wmProtocolsReply->atom,
        4,
        32,
        1,
        &wmDeleteReply->atom
    );

    xcb_map_window(this->_state->connection, this->_state->window);

    auto result = xcb_flush(this->_state->connection);
    if (result <= 0) {
        LOG_FATAL("Failed to flush xcb connection. Result: %d.", result);
        return false;
    }

    return true;
} 

void Platform::Stop() {
    XAutoRepeatOn(this->_state->display);
    xcb_destroy_window(this->_state->connection, this->_state->window);
} 

bool Platform::PumpMessages() {
    xcb_generic_event_t* event;
    auto quitFlagged = false;
    
    do {
        event = xcb_poll_for_event(this->_state->connection);
        if (event == 0) {
            break;
        }

        switch (event->response_type & -0x80) {
            case XCB_CLIENT_MESSAGE: {
                auto cm = (xcb_client_message_event_t*)event;
                if (cm->data.data32[0] == this->_state->wmDeleteWindow) {
                    quitFlagged = true;
                } 
            } break;
            case XCB_KEY_PRESS:
                break;
            case XCB_KEY_RELEASE:
                break;
            case XCB_BUTTON_PRESS:
                break;
            case XCB_BUTTON_RELEASE:
                break;
            case XCB_MOTION_NOTIFY:
                break;
            case XCB_CONFIGURE_NOTIFY:
                break;
            default:
                break;
        }

        free(event);
    } while (event != 0);

    return !quitFlagged;
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

void* Platform::MemorySet(void* destination, const int value, const unsigned long long int size) {
    return memset(destination, value, size);
} 

const char* GetFlagForColor(const LogLevel color)
{
    switch (color)
    {
        case LOG_LEVEL_FATAL:
            return "0;41";
        case LOG_LEVEL_ERROR:
            return "1;31";
        case LOG_LEVEL_WARN:
            return "1;33";
        case LOG_LEVEL_INFO:
            return "1;32";
        case LOG_LEVEL_DEBUG:
            return "1;34";
        case LOG_LEVEL_TRACE:
            return "1;30";
    };
}

void Platform::ConsoleWrite(const char* message, const LogLevel level) {
    printf("\033[%sm%s\033[0m", GetFlagForColor(level), message);
}

void Platform::ConsoleWriteError(const char* message, const LogLevel level) {
    printf("\033[%sm%s\033[0m", GetFlagForColor(level), message);
} 

double Platform::GetTime() const {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return now.tv_sec + now.tv_nsec * 0.000000001;
} 

void Platform::PSleep(const unsigned long long int milliseconds) const {
#if _POSIX_C_SOURCE >= 199309L
    struct timespec timeSpec;
    timeSpec.tv_sec = milliseconds / 1000;
    timeSpec.tv_nsec = (milliseconds % 1000) * 1000 * 1000;
    nanosleep(&timeSpec, 0);
#else
    if (milliseconds >= 1000) {
        sleep(milliseconds / 1000);
    }
    usleep((milliseconds % 1000) * 1000);
#endif
} 

#endif
