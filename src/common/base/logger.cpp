#include "logger.h"

Logger::Logger() :
    file_max_size(1048576 * 20), // 20MB
    file_max_num(20),
    level(spdlog::level::info)
{
}
std::shared_ptr<spdlog::logger> Logger::get_main_logger()
{
    return get_named_logger("main");
}

std::shared_ptr<spdlog::logger> Logger::get_named_logger(std::string &&logger_name)
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

void Logger::set_logger_level(spdlog::level::level_enum level)
{
    this->level = level;
}
void Logger::reset_logger_level(std::shared_ptr<spdlog::logger> logger)
{
    logger->set_level(level);
}
