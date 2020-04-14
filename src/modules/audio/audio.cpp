#include <iomanip>
#include <iostream>

#include "modules/audio/audio.hpp"

bool Audio::init()
{
    const auto info = Pa_GetVersionInfo();
    std::cout << "Using " << info->versionText << std::endl;

    std::cout << "Initializing PortAudio" << std::endl;
    auto error = Pa_Initialize();
    if (error != paNoError)
    {
        std::cout << "Could not initialize PortAudio: " << error << std::endl;
        return false;
    }

    const auto count = Pa_GetDeviceCount();
    std::cout << "There are " << count << " devices available." << std::endl;

    for (auto i = 0; i < count; ++i)
    {
        const auto info = Pa_GetDeviceInfo(i);
        const auto apiInfo = Pa_GetHostApiInfo(info->hostApi);
        if (info->maxInputChannels == 0)
        {
            continue;
        }
        std::cout << std::setw(2) << i << " : [" << apiInfo->name << "] [in "
                  << info->maxInputChannels << "] [out "
                  << info->maxOutputChannels << "] " << info->name << std::endl;
    }

    auto deviceIndex = -1;
    while (deviceIndex < 0 || deviceIndex > count)
    {
        std::cout << "Please specify the device index to open:" << std::endl;
        std::cin >> deviceIndex;
    }
    const auto deviceInfo = Pa_GetDeviceInfo(deviceIndex);

    const auto inParams = PaStreamParameters{
        deviceIndex, 1, paFloat32, deviceInfo->defaultLowInputLatency, NULL};

    error = Pa_OpenStream(
        &m_stream,
        &inParams,
        NULL,
        deviceInfo->defaultSampleRate,
        paFramesPerBufferUnspecified,
        paNoFlag,
        NULL,
        NULL);
    if (error != paNoError)
    {
        std::cout << "Could not open stream: " << error << std::endl;
        return false;
    }

    error = Pa_StartStream(m_stream);
    if (error != paNoError)
    {
        std::cout << "Could not start stream: " << error << std::endl;
        return false;
    }

    return true;
}

void Audio::deinit()
{
    std::cout << "Shutting down PortAudio" << std::endl;

    auto error = Pa_StopStream(m_stream);
    if (error != paNoError)
    {
        std::cout << "Error while stopping stream: " << error << std::endl;
    }

    error = Pa_CloseStream(m_stream);
    if (error != paNoError)
    {
        std::cout << "Error while closing stream: " << error << std::endl;
    }

    error = Pa_Terminate();
    if (error != paNoError)
    {
        std::cout << "Error during PortAudio shutdown: " << error << std::endl;
    }
}

void Audio::process() {}
