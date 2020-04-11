#include <memory>

#include "base/module.hpp"

template <class O>
class Output : Module
{
protected:
    std::shared_ptr<O> m_output;

public:
    std::shared_ptr<O> getResultRef();
};
