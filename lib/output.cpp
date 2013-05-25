#include "output.hpp"

namespace unit_thread_output {
    template<>
    std::string convert(const uint8_t& t) {
        std::stringstream stream;
        stream << "0x" << std::hex << static_cast<int>(t);
        return stream.str();
    }
}
