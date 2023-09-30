#include "Logger.hpp"

#include <iostream>

namespace Charly {

    void Logger::log(const std::string& str) {
        std::cout << str << std::endl;
    }

}
