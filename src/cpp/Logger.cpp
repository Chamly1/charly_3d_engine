#include "Logger.hpp"

#include <iostream>
#include <chrono>
#include <ctime>

namespace Charly {

    Logger::Logger() : mStream(std::cout) {

    }

    Logger& Logger::getInstance() {
        static Logger instance;
        return instance;
    }

    void Logger::logPrefix(LogLevel logLevel, const std::string& file, int line) {
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
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S.", &tm);

        // Print the formatted time with milliseconds
        mStream << "[" << buffer << ms % 1000 << "] [" << getLogLevelStr(logLevel) << "] [" << file << ":" << line << "] ";
    }

}
