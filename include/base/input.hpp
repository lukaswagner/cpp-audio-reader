#include <memory>

#include "base/module.hpp"

template <class I>
class Input : Module
{
protected:
    std::shared_ptr<I> m_input;

public:
    void setInputRef(std::shared_ptr<I> input);
};
