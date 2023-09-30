#include <core/logging/logger.hpp>
#include <string>

int main(void) {
    Logger logger;
    logger.LogFatal("Hello, world!");
    logger.LogError("Hello, world!");
    logger.LogWarning("Hello, world!");
    logger.LogInformation("Hello, world!");
    logger.LogDebug("Hello, world!");
    logger.LogTrace("Hello, world!");

    return 0;
}
