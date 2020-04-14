#include "modules/test/log.hpp"

#include <iostream>

void Log::process()
{
    const auto& in = std::get<0>(m_input)->read();

    std::cout << in << std::endl;
}
