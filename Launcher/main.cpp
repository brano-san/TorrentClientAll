#include <quill/std/FilesystemPath.h>
#include <quill/std/Array.h>
#include <quill/std/Vector.h>
#include "Logger.hpp"

#include <iostream>
#include <filesystem>

int main(int argc, char *argv[])
{
    LOG_CRITICAL(Core, "Program started from {}", std::filesystem::current_path());

    try
    {
        LOG_TRACE_L3(Core, "Core - LOG_TRACE_L3 {}");
        LOG_TRACE_L2(Core, "Core - LOG_TRACE_L2");
        LOG_TRACE_L1(Core, "Core - LOG_TRACE_L1");
        LOG_DEBUG(Core, "Core - LOG_DEBUG");
        LOG_INFO(Core, "Core - LOG_INFO {}");
        LOG_NOTICE(Core, "Core - LOG_NOTICE");
        LOG_WARNING(Core, "Core - LOG_WARNING");
        LOG_ERROR(Core, "Core - LOG_ERROR");
        LOG_CRITICAL(Core, "Core - LOG_CRITICAL");
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << '\n';
    }

    for (uint8_t i = 0; i < 40; ++i)
    {
        LOG_INFO_LIMIT_EVERY_N(Core, 10, "There should be 4 of these logs");
    }

    const int var_a         = 123;
    const std::string var_b = "test";
    for (uint32_t i = 0; i < 20; ++i)
    {
        // Will only log the message once per second
        LOG_INFO_LIMIT_TIME(Core, std::chrono::seconds{1}, "A json message with {var_1} and {var_2}", var_a, var_b);
        if (i % 10 == 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds{(i / 10) * 500});
        }
    }

    try
    {
        LOG_INFO(Core, "BEFORE backtrace Example {}", 1);

        LOG_BACKTRACE(Core, "Backtrace log {}", 1);
        LOG_BACKTRACE(Core, "Backtrace log {}", 2);
        LOG_BACKTRACE(Core, "Backtrace log {}", 3);
        LOG_BACKTRACE(Core, "Backtrace log {}", 4);

        LOG_INFO(Core, "AFTER backtrace Example {}", 1);

        LOG_ERROR(Core, "An error has happened, Backtrace is also flushed.");
        LOG_ERROR(Core, "An second error has happened, but backtrace is now empty.");

        LOG_BACKTRACE(Core, "Another Backtrace log {}", 1);
        LOG_BACKTRACE(Core, "Another Backtrace log {}", 2);

        LOG_INFO(Core, "Another log info");
        LOG_CRITICAL(Core, "A critical error from different logger.");
        LOG_CRITICAL(Core, "A critical error from the logger we had a backtrace.");

        const uint8_t myVariable = 5;
        LOGV_INFO(Core, "VALUE LOG", myVariable);
    }
    catch (const std::exception& ex)
    {
        LOG_ERROR(Core, "Exception {}", ex.what());
    }

    std::vector<uint32_t> vec{5, 6, 7, 8, 9};
    LOGV_INFO(Core, "Vector Log", vec);

    std::array<uint32_t, 5> arr{5, 6, 7, 8, 9};
    LOGV_INFO(Core, "Array Log", arr);

    uint32_t a;
    std::cin >> a;
    return 0;
}
