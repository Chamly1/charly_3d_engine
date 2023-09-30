#include "Logger.hpp"

#include <iostream>
#include <chrono>
#include <ctime>

namespace Charly {

    void Logger::log(LogLevel logLevel, const std::string& file, int line, const std::string& message) {

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
        std::cout << "[" << buffer << ms % 1000 << "] [" << getLogLevelStr(logLevel) << "] [" << file << ":" << line << "] " << message << std::endl;
    }

}
