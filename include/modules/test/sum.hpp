#pragma once

#include "base/combinedModule.hpp"

class Sum : public Module<ModuleInputs<float, float>, ModuleOutputs<float>>
{
public:
    Sum();
    void process() override;
};
