#include "base/module.hpp"

void Module::process()
{
}

bool Module::init()
{
    return true;
}

void Module::deinit()
{
}

void Module::prepare()
{
}

void Module::step()
{
    process();
}
