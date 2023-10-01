#include <core/logging/logger.hpp>
#include <core/assertions/assertions.hpp>
#include <string>

int main(void) {
    LOG_FATAL("Hello, world!");
    LOG_ERROR("Hello, world!");
    LOG_WARNING("Hello, world!");
    LOG_INFO("Hello, world!");
    LOG_DEBUG("Hello, world!");
    LOG_TRACE("Hello, world!");

    CASSERT(1 == 1);
    CASSERT_MESSAGE(1 == 0, "Expected to fail");

    return 0;
}
