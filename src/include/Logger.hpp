#ifndef CHARLY_3D_ENGINE_LOGGER_HPP
#define CHARLY_3D_ENGINE_LOGGER_HPP

#include <string>
#include <iostream>

#ifdef ENABLE_LOGGING

#define LOG_ERROR(message) \
    Charly::Logger::getInstance().logPrefix(Charly::LogLevel::Error, __FILE__, __LINE__); \
    Charly::Logger::getInstance() << message << '\n';

#define LOG_WARNING(message) \
    Charly::Logger::getInstance().logPrefix(Charly::LogLevel::Message, __FILE__, __LINE__); \
    Charly::Logger::getInstance() << message << '\n';

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
        std::ostream& mStream;

        Logger();

    public:
        static Logger& getInstance();

        void logPrefix(LogLevel logLevel, const std::string& file, int line);
        template <typename T>
        Logger& operator<<(const T& messageElement) {
            mStream << messageElement;
            return *this;
        }

        // delete implicit methods
        Logger(Logger const &) = delete;
        Logger & operator = (Logger const &) = delete;
        Logger(Logger &&) = delete;
        Logger & operator = (Logger &&) = delete;
    };

}

#endif //CHARLY_3D_ENGINE_LOGGER_HPP
