#pragma once

#include "base/inputModule.hpp"
#include "base/outputModule.hpp"

// class inherits prepare and step via dominance
#pragma warning(disable : 4250)

class Sum : public InputModule<float, float>, public OutputModule<float>
{
    void process() override;
    using OutputModule<float>::prepare;
};
