#include <iostream>
#include <memory>
#include <vector>

// #include "base/module.hpp"
#include "base/moduleData.hpp"
#include "modules/test/increment.hpp"
#include "modules/test/log.hpp"
#include "modules/test/sum.hpp"

int main(int argc, char const* argv[])
{
    // create modules
    auto inc = Increment();
    auto sum = Sum();
    auto logInc = Log();
    auto logSum = Log();

    auto modules = std::vector<Module>{inc, sum, logInc, logSum};

    // first, init all modules
    auto success = true;
    for (auto& m : modules)
    {
        success &= m.init();
    }

    if (!success)
    {
        // some module could not be initialized - deinit and exit
        for (auto& m : modules)
        {
            m.deinit();
        }
        return -1;
    }

    // const value for second sum input
    auto val = std::make_shared<ModuleData<float>>();
    val->write() = 3;
    val->resetChanged();

    // connect all inputs/outputs - first get outputs
    const auto incOut = inc.getOutputPtr<0>();
    const auto sumOut = sum.getOutputPtr<0>();

    // inc feeds into itself
    inc.setInputPtr<0>(incOut);

    // sum adds up inc and val
    sum.setInputPtr<0>(incOut);
    sum.setInputPtr<1>(val);

    // log out both outputs
    logInc.setInputPtr<0>(incOut);
    logSum.setInputPtr<0>(sumOut);

    // main loop - only run three times
    for (auto i = 0; i < 3; i++)
    {
        // prepare mainly resets the changed flag of module outputs
        for (auto& m : modules)
        {
            m.prepare();
        }

        inc.step();
        sum.step();
        std::cout << "Inc value: ";
        logInc.step();
        std::cout << "Sum value: ";
        logSum.step();
    }

    // clean up
    for (auto& m : modules)
    {
        m.deinit();
    }

    return 0;
}
