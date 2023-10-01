#ifndef CHARLY_3D_ENGINE_LOGGER_HPP
#define CHARLY_3D_ENGINE_LOGGER_HPP

#include <string>
#include <iostream>

#ifdef ENABLE_LOGGING

#define LOG_ERROR(...) \
    Charly::Logger::getInstance().log(Charly::LogLevel::Error, __FILE__, __LINE__, __VA_ARGS__);

#define LOG_WARNING(...) \
    Charly::Logger::getInstance().log(Charly::LogLevel::Warning, __FILE__, __LINE__, __VA_ARGS__);

#else

#define LOG_ERROR(...)
#define LOG_WARNING(...)

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
        std::ostream& mStream;
        char mTimeBuff[80];
        char mMessageBuff[1024];

        Logger();
        void prepareTimeBuff();

    public:
        static Logger& getInstance();

        void log(LogLevel logLevel, const char* fileName, int line, const char* messageFormat, ...);

        // delete implicit methods
        Logger(Logger const &) = delete;
        Logger & operator = (Logger const &) = delete;
        Logger(Logger &&) = delete;
        Logger & operator = (Logger &&) = delete;
    };

}

#endif //CHARLY_3D_ENGINE_LOGGER_HPP
