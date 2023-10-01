#include "Logger.hpp"

#include <iostream>
#include <chrono>
#include <ctime>
#include <cstdarg>

namespace Charly {

    Logger::Logger() : mStream(std::cout) {

    }

    void Logger::prepareTimeBuff() {
        // Get the current system time with milliseconds
        auto now = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

        // Convert the milliseconds to a time_point
        std::chrono::system_clock::time_point tp = std::chrono::system_clock::time_point(std::chrono::milliseconds(ms));

        // Convert the time_point to a time_t (seconds since epoch)
        std::time_t time = std::chrono::system_clock::to_time_t(tp);

        // Format the time with milliseconds
        std::tm tm = *std::localtime(&time);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
        std::snprintf(mTimeBuff, sizeof(mTimeBuff), "%s.%lld", buffer, ms % 1000);
    }

    Logger& Logger::getInstance() {
        static Logger instance;
        return instance;
    }

    void Logger::log(LogLevel logLevel, const char* fileName, int line, const char* messageFormat, ...) {
        prepareTimeBuff();

        va_list args;
        va_start(args, messageFormat);
        std::vsnprintf(mMessageBuff, sizeof(mMessageBuff), messageFormat, args);
        va_end(args);

        std::printf("[%s] [%s] [%s:%d] %s\n", mTimeBuff, getLogLevelStr(logLevel), fileName, line, mMessageBuff);
    }

}
