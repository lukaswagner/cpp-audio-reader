#include "modules/test/sum.hpp"

void Sum::process()
{
    const auto& first = std::get<0>(m_input)->read();
    const auto& second = std::get<1>(m_input)->read();
    auto& result = std::get<0>(m_output)->write();

    result = first + second;
}