#ifndef CHARLY_3D_ENGINE_LOGGER_HPP
#define CHARLY_3D_ENGINE_LOGGER_HPP

#include <string>

#ifdef ENABLE_LOGGING

#define LOG_ERROR(str) \
    Charly::Logger::log(Charly::LogLevel::Error, __FILE__, __LINE__, str);

#define LOG_WARNING(str) \
    Charly::Logger::log(Charly::LogLevel::Warning, __FILE__, __LINE__, str);

#else

#define LOG_ERROR(str)
#define LOG_WARNING(str)

#endif

// target log format: [YYYY-MM-DD HH:MM:SS.MMM] [LogLevel] [Module] [File:Line] Message

namespace Charly {

    enum class LogLevel {
        Error, Warning, Debug, Info, Fatal
    };

    inline const char* getLogLevelStr(LogLevel logLevel) {
        switch (logLevel) {
            case LogLevel::Error:       return "ERROR";
            case LogLevel::Warning:     return "WARNING";
            case LogLevel::Debug:       return "DEBUG";
            case LogLevel::Info:        return "INFO";
            case LogLevel::Fatal:       return "FATAL";
        }

        return "";
    }

    class Logger {
    private:


    public:
        static void log(LogLevel logLevel, const std::string& file, int line, const std::string& message);

        // delete implicit methods
        Logger(Logger const &) = delete;
        Logger & operator = (Logger const &) = delete;
        Logger(Logger &&) = delete;
        Logger & operator = (Logger &&) = delete;
    };

}

#endif //CHARLY_3D_ENGINE_LOGGER_HPP
