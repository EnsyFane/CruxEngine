#include <core/logging/logger.hpp>
#include <core/assertions/assertions.hpp>
#include <platform/platform.hpp>

#include <string>

int main(void) {
    LOG_FATAL("Hello, world!");
    LOG_ERROR("Hello, world!");
    LOG_WARNING("Hello, world!");
    LOG_INFO("Hello, world!");
    LOG_DEBUG("Hello, world!");
    LOG_TRACE("Hello, world!");

    Platform platform;
    if (platform.Initialize("Testbed", 100, 100, 1280, 720)) {
        LOG_INFO("Platform initialized successfully.");
        while (true) {
            platform.PumpMessages();
        }
        platform.Stop();
    } else {
        LOG_FATAL("Platform failed to initialize.");
    }
    

    return 0;
}
