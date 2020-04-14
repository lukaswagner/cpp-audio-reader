#pragma once

#include <map>
#include <memory>
#include <string>

#include "base/module.hpp"
#include "base/moduleData.hpp"

template <class... T>
class OutputModule : virtual public Module
{
protected:
    ModuleDataList<T...> m_output;

public:
    OutputModule()
    {
        m_output = std::make_tuple(std::make_shared<ModuleData<T>>()...);
    }

    template <int i, class t = std::tuple_element<i, std::tuple<T...>>::type>
    ModuleDataPtr<t> getOutputPtr()
    {
        return std::get<i>(m_output);
    }

    void prepare() override
    {
        std::apply(
            [](auto&&... data) { ((data->resetChanged()), ...); }, m_output);
    }
};
