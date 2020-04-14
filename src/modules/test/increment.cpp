#include "modules/test/increment.hpp"

void Increment::process()
{
    const auto& in = std::get<0>(m_input)->read();
    auto& out = std::get<0>(m_output)->write();

    out = in + 1;
}
