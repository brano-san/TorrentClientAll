#pragma once

#include <GenEnum.hpp>
#include <logger/CategorizedLogger/CategorizedLogger.hpp>

namespace logger {
static constexpr uint8_t kLoggerBacktraceLenght = 32;
GENENUM(uint8_t, CoreLauncherSource, Core);
DEFINE_CAT_LOGGER_MODULE(CoreLauncher, CoreLauncherSources, kLoggerBacktraceLenght);
}  // namespace logger

// clang-format off
#define LOG(level, name, message, ...)                      CAT_LOG_##level(CoreLauncher, CoreLauncherSources, name, message, ##__VA_ARGS__) // NOLINT(cppcoreguidelines-avoid-do-while)
#define LOGV(level, name, message, ...)                     CAT_LOGV_##level(CoreLauncher, CoreLauncherSources, name, message, ##__VA_ARGS__) // NOLINT(cppcoreguidelines-avoid-do-while)
#define LOG_LIMIT_TIME(level, name, time, message, ...)     CAT_LOG_##level##_LIMIT_TIME(CoreLauncher, CoreLauncherSources, name, time, message, ##__VA_ARGS__) // NOLINT(cppcoreguidelines-avoid-do-while)
#define LOG_LIMIT_EVERY_N(level, name, count, message, ...) CAT_LOG_##level##_LIMIT_EVERY_N(CoreLauncher, CoreLauncherSources, name, count, message, ##__VA_ARGS__) // NOLINT(cppcoreguidelines-avoid-do-while)

#define LOG_TRACE_L3(name, message, ...)  LOG(TRACE_L3,  name, message, ##__VA_ARGS__)
#define LOG_TRACE_L2(name, message, ...)  LOG(TRACE_L2,  name, message, ##__VA_ARGS__)
#define LOG_TRACE_L1(name, message, ...)  LOG(TRACE_L1,  name, message, ##__VA_ARGS__)
#define LOG_DEBUG(name, message, ...)     LOG(DEBUG,     name, message, ##__VA_ARGS__)
#define LOG_INFO(name, message, ...)      LOG(INFO,      name, message, ##__VA_ARGS__)
#define LOG_NOTICE(name, message, ...)    LOG(NOTICE,    name, message, ##__VA_ARGS__)
#define LOG_WARNING(name, message, ...)   LOG(WARNING,   name, message, ##__VA_ARGS__)
#define LOG_ERROR(name, message, ...)     LOG(ERROR,     name, message, ##__VA_ARGS__)
#define LOG_CRITICAL(name, message, ...)  LOG(CRITICAL,  name, message, ##__VA_ARGS__)
#define LOG_BACKTRACE(name, message, ...) LOG(BACKTRACE, name, message, ##__VA_ARGS__)

#define LOGV_TRACE_L3(name, message, ...)  LOGV(TRACE_L3,  name, message, ##__VA_ARGS__)
#define LOGV_TRACE_L2(name, message, ...)  LOGV(TRACE_L2,  name, message, ##__VA_ARGS__)
#define LOGV_TRACE_L1(name, message, ...)  LOGV(TRACE_L1,  name, message, ##__VA_ARGS__)
#define LOGV_DEBUG(name, message, ...)     LOGV(DEBUG,     name, message, ##__VA_ARGS__)
#define LOGV_INFO(name, message, ...)      LOGV(INFO,      name, message, ##__VA_ARGS__)
#define LOGV_NOTICE(name, message, ...)    LOGV(NOTICE,    name, message, ##__VA_ARGS__)
#define LOGV_WARNING(name, message, ...)   LOGV(WARNING,   name, message, ##__VA_ARGS__)
#define LOGV_ERROR(name, message, ...)     LOGV(ERROR,     name, message, ##__VA_ARGS__)
#define LOGV_CRITICAL(name, message, ...)  LOGV(CRITICAL,  name, message, ##__VA_ARGS__)
#define LOGV_BACKTRACE(name, message, ...) LOGV(BACKTRACE, name, message, ##__VA_ARGS__)

#define LOG_TRACE_L3_LIMIT_TIME(name, time, message, ...) LOG_LIMIT_TIME(TRACE_L3, name, time, message, ##__VA_ARGS__)
#define LOG_TRACE_L2_LIMIT_TIME(name, time, message, ...) LOG_LIMIT_TIME(TRACE_L2, name, time, message, ##__VA_ARGS__)
#define LOG_TRACE_L1_LIMIT_TIME(name, time, message, ...) LOG_LIMIT_TIME(TRACE_L1, name, time, message, ##__VA_ARGS__)
#define LOG_DEBUG_LIMIT_TIME(name, time, message, ...)    LOG_LIMIT_TIME(DEBUG,    name, time, message, ##__VA_ARGS__)
#define LOG_INFO_LIMIT_TIME(name, time, message, ...)     LOG_LIMIT_TIME(INFO,     name, time, message, ##__VA_ARGS__)
#define LOG_NOTICE_LIMIT_TIME(name, time, message, ...)   LOG_LIMIT_TIME(NOTICE,   name, time, message, ##__VA_ARGS__)
#define LOG_WARNING_LIMIT_TIME(name, time, message, ...)  LOG_LIMIT_TIME(WARNING,  name, time, message, ##__VA_ARGS__)
#define LOG_ERROR_LIMIT_TIME(name, time, message, ...)    LOG_LIMIT_TIME(ERROR,    name, time, message, ##__VA_ARGS__)
#define LOG_CRITICAL_LIMIT_TIME(name, time, message, ...) LOG_LIMIT_TIME(CRITICAL, name, time, message, ##__VA_ARGS__)

#define LOG_TRACE_L3_LIMIT_EVERY_N(name, count, message, ...) LOG_LIMIT_EVERY_N(TRACE_L3, name, count, message, ##__VA_ARGS__)
#define LOG_TRACE_L2_LIMIT_EVERY_N(name, count, message, ...) LOG_LIMIT_EVERY_N(TRACE_L2, name, count, message, ##__VA_ARGS__)
#define LOG_TRACE_L1_LIMIT_EVERY_N(name, count, message, ...) LOG_LIMIT_EVERY_N(TRACE_L1, name, count, message, ##__VA_ARGS__)
#define LOG_DEBUG_LIMIT_EVERY_N(name, count, message, ...)    LOG_LIMIT_EVERY_N(DEBUG,    name, count, message, ##__VA_ARGS__)
#define LOG_INFO_LIMIT_EVERY_N(name, count, message, ...)     LOG_LIMIT_EVERY_N(INFO,     name, count, message, ##__VA_ARGS__)
#define LOG_NOTICE_LIMIT_EVERY_N(name, count, message, ...)   LOG_LIMIT_EVERY_N(NOTICE,   name, count, message, ##__VA_ARGS__)
#define LOG_WARNING_LIMIT_EVERY_N(name, count, message, ...)  LOG_LIMIT_EVERY_N(WARNING,  name, count, message, ##__VA_ARGS__)
#define LOG_ERROR_LIMIT_EVERY_N(name, count, message, ...)    LOG_LIMIT_EVERY_N(ERROR,    name, count, message, ##__VA_ARGS__)
#define LOG_CRITICAL_LIMIT_EVERY_N(name, count, message, ...) LOG_LIMIT_EVERY_N(CRITICAL, name, count, message, ##__VA_ARGS__)
// clang-format on
