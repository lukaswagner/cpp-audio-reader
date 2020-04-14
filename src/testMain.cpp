#include <iostream>
#include <memory>
#include <vector>

#include "base/combinedModule.hpp"
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

    auto modules = std::vector<IModule>{inc, sum, logInc, logSum};

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
    auto val = std::make_shared<ModuleOutput<float>>();

    // connect all inputs/outputs - first get outputs
    const auto incOut = inc.output<0>();
    const auto sumOut = sum.output<0>();

    // inc feeds into itself
    incOut->connect(inc.input<0>());

    // sum adds up inc and val
    incOut->connect(sum.input<0>());
    val->connect(sum.input<1>());

    // log out both outputs
    incOut->connect(logInc.input<0>());
    sumOut->connect(logSum.input<0>());

    // set constant value
    val->write() = 3.0f;

    // main loop - only run three times
    for (auto i = 0; i < 3; i++)
    {
        inc.update();
        sum.update();
        std::cout << "Inc value: ";
        logInc.update();
        std::cout << "Sum value: ";
        logSum.update();
    }

    // clean up
    for (auto& m : modules)
    {
        m.deinit();
    }

    return 0;
}
