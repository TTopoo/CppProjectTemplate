#ifndef LOGGER_H
#define LOGGER_H

#include "stdafx.h"

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/spdlog.h>

class Logger
{
public:
    Logger();
    std::shared_ptr<spdlog::logger> get_main_logger();
    std::shared_ptr<spdlog::logger> get_named_logger(std::string &&logger_name);

    void set_logger_level(spdlog::level::level_enum level);
    void reset_logger_level(std::shared_ptr<spdlog::logger> logger);

private:
    size_t file_max_size;
    size_t file_max_num;
    spdlog::level::level_enum level;
};

class LoggerSingleton : public Singleton<Logger>
{
};

#endif // LOGGER_H
