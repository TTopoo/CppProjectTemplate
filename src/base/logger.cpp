#include "logger.h"

Logger::Logger() :
    file_max_size(1048576 * 20), // 20MB
    file_max_num(20),
    level(spdlog::level::info)
{
}
Logger &Logger::get_instance()
{
    static Logger instance;
    return instance;
}

std::shared_ptr<spdlog::logger> Logger::get_main_logger()
{
    return get_instance()._get_main_logger();
}

std::shared_ptr<spdlog::logger> Logger::get_named_logger(std::string &&logger_name)
{
    return get_instance()._get_named_logger(logger_name);
}

void Logger::reset_logger_level(std::shared_ptr<spdlog::logger> logger)
{
    if (logger == nullptr)
        logger = get_main_logger();

    auto before_level = logger->level();
    auto after_level = get_instance().level;
    if (before_level == after_level)
    {
        SPDLOG_LOGGER_INFO(get_main_logger(), "log level is same");
        return;
    }
    SPDLOG_LOGGER_INFO(get_main_logger(), "level from {} to {}", spdlog::level::to_string_view(before_level), spdlog::level::to_string_view(after_level));
    get_instance()._reset_logger_level(logger);
}

std::shared_ptr<spdlog::logger> Logger::_get_main_logger()
{
    return get_named_logger("main");
}

std::shared_ptr<spdlog::logger> Logger::_get_named_logger(std::string &logger_name)
{
    auto logger = spdlog::get(logger_name);
    if (!logger)
    {
        logger = spdlog::rotating_logger_mt(logger_name, "log/" + logger_name + ".txt", file_max_size, file_max_num);
        logger->set_pattern("[%H:%M:%S.%e][%t] [" + logger_name + "][%l]: %v"); // (%@)
        spdlog::set_level(spdlog::level::trace);
        logger->flush_on(spdlog::level::trace);
    }
    return logger;
}

void Logger::_set_logger_level(spdlog::level::level_enum level)
{
    this->level = level;
}
void Logger::_reset_logger_level(std::shared_ptr<spdlog::logger> logger)
{
    logger->set_level(level);
}
