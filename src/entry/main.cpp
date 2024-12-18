#include "../base/logger.h"
#include "../base/stdafx.h"

int main(int argc, char *argv[])
{
    std::cout << "Hello, World!" << std::endl;
    SPDLOG_LOGGER_INFO(Logger::get_main_logger(), "Hello, World!");
    return 0;
}
