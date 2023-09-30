#ifndef CHARLY_3D_ENGINE_LOGGER_HPP
#define CHARLY_3D_ENGINE_LOGGER_HPP

#include <string>

#ifdef ENABLE_LOGGING

#define LOG(str) \
    Charly::Logger::log(str);

#else

#define LOG(str)

#endif

namespace Charly {

    class Logger {
    private:


    public:
        static void log(const std::string& str);

        // delete implicit methods
        Logger(Logger const &) = delete;
        Logger & operator = (Logger const &) = delete;
        Logger(Logger &&) = delete;
        Logger & operator = (Logger &&) = delete;
    };

}

#endif //CHARLY_3D_ENGINE_LOGGER_HPP
