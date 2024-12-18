#ifndef LOGGER_H
#define LOGGER_H

#include "stdafx.h"

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/spdlog.h>

class Logger
{
public:
    static Logger &get_instance();
    static std::shared_ptr<spdlog::logger> get_main_logger();
    static std::shared_ptr<spdlog::logger> get_named_logger(std::string &&logger_name);
    static void reset_logger_level(std::shared_ptr<spdlog::logger> logger = nullptr);

private:
    Logger();
    Logger(Logger const &) = delete;
    Logger &operator=(Logger const &) = delete;

    std::shared_ptr<spdlog::logger> _get_main_logger();
    std::shared_ptr<spdlog::logger> _get_named_logger(std::string &logger_name);

    void _set_logger_level(spdlog::level::level_enum level);
    void _reset_logger_level(std::shared_ptr<spdlog::logger> logger);

    size_t file_max_size;
    size_t file_max_num;
    spdlog::level::level_enum level;
};

#endif // LOGGER_H
