#pragma once

#include <memory>
#include <vector>

// forward declare to resolve cyclic dependency
template <class T>
class ModuleInput;

template <class T>
class ModuleOutput
{
protected:
    std::shared_ptr<T> m_data;
    std::vector<std::shared_ptr<ModuleInput<T>>> m_connectedInputs;

public:
    ModuleOutput()
    {
        m_data = std::make_shared<T>();
    }

    void connect(std::shared_ptr<ModuleInput<T>> input)
    {
        m_connectedInputs.push_back(input);
        input->connect(m_data);
    }

    T& write()
    {
        for (auto& i : m_connectedInputs)
        {
            i->setChanged();
        }
        return *m_data;
    }
};
