#pragma once

#include <vector>

#include <portaudio.h>

#include "base/outputModule.hpp"

typedef std::vector<float> ChannelHistory;

// struct AudioHistory
// {
//     std::vector<ChannelHistory>
// }

class Audio : OutputModule<std::vector<float>>
{
protected:
    PaStream* m_stream;

public:
    bool init() override;
    void deinit() override;
    void process() override;
};
