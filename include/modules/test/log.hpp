#pragma once

#include "base/inputModule.hpp"

class Log : public InputModule<float>
{
    void process() override;
};
