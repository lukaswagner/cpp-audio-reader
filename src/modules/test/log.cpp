#include "modules/test/log.hpp"

#include <iostream>

Log::Log() : Module()
{
    input<0>() = std::make_shared<ModuleInput<float>>();
}

void Log::process()
{
    const auto& in = read<0>();

    std::cout << in << std::endl;
}
