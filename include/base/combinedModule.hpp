#pragma once

#include <memory>
#include <tuple>

#include "base/moduleInput.hpp"
#include "base/moduleOutput.hpp"

template <typename... T>
using ModuleInputs = std::tuple<std::shared_ptr<ModuleInput<T>>...>;

template <typename... T>
using ModuleOutputs = std::tuple<std::shared_ptr<ModuleOutput<T>>...>;

class IModule
{
public:
    virtual bool init()
    {
        return true;
    };
    virtual void deinit(){};
    virtual void update(){};
};

// template <typename T>
// constexpr

// template <typename T, size_t... I>
// void initTupleElements(T& t){
//     // (using ptr = std::tuple_element<I, T>::type;
//     //  using elem = std::pointer_traits<ptr>::element_type;
//     //  std::get<I>(t) = std::make_shared<elem>();)...
// };

// template <typename T>
// constexpr auto getIndices()
// {
//     return std::make_index_sequence<std::tuple_size<T>::value>{};
// }

// template <typename T>
// void initTuple(T& t)
// {
//     initTupleElements<T, getIndices<T>()>(t);
// };

// template <typename T>
// constexpr auto ptrElemType()
// {
//     return std::pointer_traits<T>::element_type;
// }

// template <typename T>
// void initTuple(T& t)
// {
//     constexpr auto size = std::tuple_size<T>::value;
//     for (constexpr auto i = 0; i < size; i++)
//     {
//         using ptr = std::tuple_element<i, T>();
//         using elem = std::pointer_traits<ptr>::element_type;
//     }
//     // initTupleElements<T, getIndices<T>()>(t);
// };

template <typename T1, typename T2>
class Module : public IModule
{
protected:
    T1 m_inputs;
    T2 m_outputs;

    bool inputChanged()
    {
        auto changed = false;

        std::apply(
            [&changed](auto&&... data) { ((changed |= data->changed()), ...); },
            m_inputs);
        return changed;
    }

    void resetInputChanged()
    {
        std::apply(
            [](auto&&... data) { ((data->resetChanged()), ...); }, m_inputs);
    }

    virtual void process() = 0;

public:
    Module()
    {
        m_inputs = T1();
        // initTuple(m_inputs);
        // std::apply(
        //     [](auto&&... data) { ((data = std::make_shared()), ...); },
        //     m_inputs);
        m_outputs = T2();
    }

    template <int i, typename ptr = std::tuple_element<i, T1>::type>
    ptr& input()
    {
        return std::get<i>(m_inputs);
    }

    template <int i, typename ptr = std::tuple_element<i, T2>::type>
    ptr& output()
    {
        return std::get<i>(m_outputs);
    }

    template <int i>
    const auto& read() const
    {
        return std::get<i>(m_inputs)->read();
    }

    template <int i>
    auto& write()
    {
        return std::get<i>(m_outputs)->write();
    }

    void update() override
    {
        if (!inputChanged())
        {
            return;
        }
        resetInputChanged();

        process();
    }
};
