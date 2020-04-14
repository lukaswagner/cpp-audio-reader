#pragma once

#include "base/inputModule.hpp"
#include "base/outputModule.hpp"

// class inherits prepare and step via dominance
#pragma warning(disable : 4250)

class Increment : public InputModule<float>, public OutputModule<float>
{
public:
    void process() override;
};
