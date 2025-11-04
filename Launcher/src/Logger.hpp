#pragma once

#include <quill/std/FilesystemPath.h>
#include <GenEnum.hpp>
#include <logger/CategorizedLogger/CategorizedLogger.hpp>

namespace logger {
static constexpr uint8_t kLoggerBacktraceLenght = 32;
GENENUM(uint8_t, CoreLauncherSource, Core, FullFileReadStrategy, TorrentFileParser);
DEFINE_CAT_LOGGER_MODULE(CoreLauncher, CoreLauncherSources, kLoggerBacktraceLenght);
}  // namespace logger

// clang-format off
#define LOG(level, name, message, ...)                      CAT_LOG_##level(CoreLauncher, CoreLauncherSources, name, message, ##__VA_ARGS__) // NOLINT(cppcoreguidelines-avoid-do-while)
#define LOGV(level, name, message, ...)                     CAT_LOGV_##level(CoreLauncher, CoreLauncherSources, name, message, ##__VA_ARGS__) // NOLINT(cppcoreguidelines-avoid-do-while)
#define LOG_LIMIT_TIME(level, name, time, message, ...)     CAT_LOG_##level##_LIMIT_TIME(CoreLauncher, CoreLauncherSources, name, time, message, ##__VA_ARGS__) // NOLINT(cppcoreguidelines-avoid-do-while)
#define LOG_LIMIT_EVERY_N(level, name, count, message, ...) CAT_LOG_##level##_LIMIT_EVERY_N(CoreLauncher, CoreLauncherSources, name, count, message, ##__VA_ARGS__) // NOLINT(cppcoreguidelines-avoid-do-while)

#define LOGT_L3(name, message, ...) LOG(TRACE_L3,  name, message, ##__VA_ARGS__)
#define LOGT_L2(name, message, ...) LOG(TRACE_L2,  name, message, ##__VA_ARGS__)
#define LOGT_L1(name, message, ...) LOG(TRACE_L1,  name, message, ##__VA_ARGS__)
#define LOGD(name, message, ...)    LOG(DEBUG,     name, message, ##__VA_ARGS__)
#define LOGI(name, message, ...)    LOG(INFO,      name, message, ##__VA_ARGS__)
#define LOGN(name, message, ...)    LOG(NOTICE,    name, message, ##__VA_ARGS__)
#define LOGW(name, message, ...)    LOG(WARNING,   name, message, ##__VA_ARGS__)
#define LOGE(name, message, ...)    LOG(ERROR,     name, message, ##__VA_ARGS__)
#define LOGC(name, message, ...)    LOG(CRITICAL,  name, message, ##__VA_ARGS__)
#define LOGB(name, message, ...)    LOG(BACKTRACE, name, message, ##__VA_ARGS__)

#define LOGVT_L3(name, message, ...) LOGV(TRACE_L3,  name, message, ##__VA_ARGS__)
#define LOGVT_L2(name, message, ...) LOGV(TRACE_L2,  name, message, ##__VA_ARGS__)
#define LOGVT_L1(name, message, ...) LOGV(TRACE_L1,  name, message, ##__VA_ARGS__)
#define LOGVD(name, message, ...)    LOGV(DEBUG,     name, message, ##__VA_ARGS__)
#define LOGVI(name, message, ...)    LOGV(INFO,      name, message, ##__VA_ARGS__)
#define LOGVN(name, message, ...)    LOGV(NOTICE,    name, message, ##__VA_ARGS__)
#define LOGVW(name, message, ...)    LOGV(WARNING,   name, message, ##__VA_ARGS__)
#define LOGVE(name, message, ...)    LOGV(ERROR,     name, message, ##__VA_ARGS__)
#define LOGVC(name, message, ...)    LOGV(CRITICAL,  name, message, ##__VA_ARGS__)
#define LOGVB(name, message, ...)    LOGV(BACKTRACE, name, message, ##__VA_ARGS__)

#define LOGT_L3_LIMIT_TIME(name, time, message, ...) LOG_LIMIT_TIME(TRACE_L3, name, time, message, ##__VA_ARGS__)
#define LOGT_L2_LIMIT_TIME(name, time, message, ...) LOG_LIMIT_TIME(TRACE_L2, name, time, message, ##__VA_ARGS__)
#define LOGT_L1_LIMIT_TIME(name, time, message, ...) LOG_LIMIT_TIME(TRACE_L1, name, time, message, ##__VA_ARGS__)
#define LOGD_LIMIT_TIME(name, time, message, ...)    LOG_LIMIT_TIME(DEBUG,    name, time, message, ##__VA_ARGS__)
#define LOGI_LIMIT_TIME(name, time, message, ...)    LOG_LIMIT_TIME(INFO,     name, time, message, ##__VA_ARGS__)
#define LOGN_LIMIT_TIME(name, time, message, ...)    LOG_LIMIT_TIME(NOTICE,   name, time, message, ##__VA_ARGS__)
#define LOGW_LIMIT_TIME(name, time, message, ...)    LOG_LIMIT_TIME(WARNING,  name, time, message, ##__VA_ARGS__)
#define LOGE_LIMIT_TIME(name, time, message, ...)    LOG_LIMIT_TIME(ERROR,    name, time, message, ##__VA_ARGS__)
#define LOGC_LIMIT_TIME(name, time, message, ...)    LOG_LIMIT_TIME(CRITICAL, name, time, message, ##__VA_ARGS__)

#define LOGT_L3_LIMIT_EVERY_N(name, count, message, ...) LOG_LIMIT_EVERY_N(TRACE_L3, name, count, message, ##__VA_ARGS__)
#define LOGT_L2_LIMIT_EVERY_N(name, count, message, ...) LOG_LIMIT_EVERY_N(TRACE_L2, name, count, message, ##__VA_ARGS__)
#define LOGT_L1_LIMIT_EVERY_N(name, count, message, ...) LOG_LIMIT_EVERY_N(TRACE_L1, name, count, message, ##__VA_ARGS__)
#define LOGD_LIMIT_EVERY_N(name, count, message, ...)    LOG_LIMIT_EVERY_N(DEBUG,    name, count, message, ##__VA_ARGS__)
#define LOGI_LIMIT_EVERY_N(name, count, message, ...)    LOG_LIMIT_EVERY_N(INFO,     name, count, message, ##__VA_ARGS__)
#define LOGN_LIMIT_EVERY_N(name, count, message, ...)    LOG_LIMIT_EVERY_N(NOTICE,   name, count, message, ##__VA_ARGS__)
#define LOGW_LIMIT_EVERY_N(name, count, message, ...)    LOG_LIMIT_EVERY_N(WARNING,  name, count, message, ##__VA_ARGS__)
#define LOGE_LIMIT_EVERY_N(name, count, message, ...)    LOG_LIMIT_EVERY_N(ERROR,    name, count, message, ##__VA_ARGS__)
#define LOGC_LIMIT_EVERY_N(name, count, message, ...)    LOG_LIMIT_EVERY_N(CRITICAL, name, count, message, ##__VA_ARGS__)
// clang-format on
