#pragma once

#include <memory>

template <class T>
class ModuleData
{
protected:
    T m_data;
    bool m_changed;

public:
    // accessor for read-only access
    const T& read() const
    {
        return m_data;
    }

    // accessor for read and write access
    T& write()
    {
        m_changed = true;
        return m_data;
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

template <class T>
using ModuleDataPtr = std::shared_ptr<ModuleData<T>>;

template <class... T>
using ModuleDataList = std::tuple<ModuleDataPtr<T>...>;
