#include "base/input.hpp"

template <class I>
void Input<I>::setInputRef(std::shared_ptr<I> input)
{
    m_input = input;
}
