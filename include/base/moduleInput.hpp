#pragma once

#include <memory>

// forward declare to resolve cyclic dependency
template <class T>
class ModuleOutput;

template <class T>
class ModuleInput
{
    friend ModuleOutput<T>;

protected:
    std::shared_ptr<T> m_data;
    bool m_changed;

    void connect(std::shared_ptr<T> data)
    {
        m_data = data;
        m_changed = true;
    }

    void setChanged()
    {
        m_changed = true;
    }

public:
    ModuleInput()
    {
        m_data = std::make_shared<T>();
    }

    const T& read() const
    {
        return *m_data;
    }

    bool changed() const
    {
        return m_changed;
    }

    void resetChanged()
    {
        m_changed = false;
    }
};
