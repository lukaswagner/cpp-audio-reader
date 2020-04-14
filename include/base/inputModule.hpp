#pragma once

#include <memory>
#include <string>
#include <tuple>

#include "base/module.hpp"
#include "base/moduleData.hpp"

template <class... T>
class InputModule : virtual public Module
{
protected:
    ModuleDataList<T...> m_input;
    bool inputChanged()
    {
        auto changed = false;

        std::apply(
            [&changed](auto&&... data) { ((changed |= data->changed()), ...); },
            m_input);
        return changed;
    }

public:
    template <int i, class t = std::tuple_element<i, std::tuple<T...>>::type>
    void setInputPtr(ModuleDataPtr<t> input)
    {
        std::get<i>(m_input) = input;
    }

    void step() override
    {
        // if (!inputChanged())
        // {
        //     return;
        // }

        Module::step();
    }
};
