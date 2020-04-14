#pragma once

#include "base/combinedModule.hpp"

class Log : public Module<ModuleInputs<float>, ModuleOutputs<>>
{
public:
    Log();
    void process() override;
};
