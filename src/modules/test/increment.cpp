#include "modules/test/increment.hpp"

Increment::Increment() : Module()
{
    input<0>() = std::make_shared<ModuleInput<float>>();
    output<0>() = std::make_shared<ModuleOutput<float>>();
}

void Increment::process()
{
    const auto& in = read<0>();
    auto& out = write<0>();

    out = in + 1;
}
