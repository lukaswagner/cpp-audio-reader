#include <vector>

#include <portaudio.h>

#include "base/output.hpp"

class Audio : Output<std::vector<float>>
{
protected:
    PaStream *m_stream;

public:
    bool init() override;
    void deinit() override;
    void process() override;
};
