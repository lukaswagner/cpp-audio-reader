#pragma once

#include "base/combinedModule.hpp"

class Increment : public Module<ModuleInputs<float>, ModuleOutputs<float>>
{
public:
    Increment();
    void process() override;
};
