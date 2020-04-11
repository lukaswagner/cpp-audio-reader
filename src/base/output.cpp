#include "base/output.hpp"

template <class O>
std::shared_ptr<O> Output<O>::getResultRef()
{
    return m_output;
}
