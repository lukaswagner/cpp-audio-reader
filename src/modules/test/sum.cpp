#include "modules/test/sum.hpp"

Sum::Sum() : Module()
{
    input<0>() = std::make_shared<ModuleInput<float>>();
    input<1>() = std::make_shared<ModuleInput<float>>();
    output<0>() = std::make_shared<ModuleOutput<float>>();
}

void Sum::process()
{
    const auto& first = read<0>();
    const auto& second = read<1>();
    auto& result = write<0>();

    result = first + second;
}