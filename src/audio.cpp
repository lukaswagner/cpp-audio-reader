#include <iomanip>
#include <iostream>

#include "audio.hpp"

bool Audio::init()
{
    const auto info = Pa_GetVersionInfo();
    std::cout << "Using " << info->versionText << std::endl;

    std::cout << "Initializing PortAudio" << std::endl;
    auto error = Pa_Initialize();
    if (error != paNoError)
    {
        std::cout << "Could not initialize PortAudio. Error code: " << error
                  << std::endl;
        return false;
    }

    const auto count = Pa_GetDeviceCount();
    std::cout << "There are " << count << " devices available." << std::endl;

    for (auto i = 0; i < count; ++i)
    {
        const auto info = Pa_GetDeviceInfo(i);
        const auto apiInfo = Pa_GetHostApiInfo(info->hostApi);
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
        deviceIndex, 2, paFloat32, deviceInfo->defaultLowInputLatency, NULL};

    error = Pa_OpenStream(
        &m_stream,
        &inParams,
        NULL,
        deviceInfo->defaultSampleRate,
        0,
        0,
        NULL,
        NULL);

    if (error != paNoError)
    {
        std::cout << "Could not open stream. Error code: " << error
                  << std::endl;
        return false;
    }

    return true;
}

void Audio::deinit()
{
    std::cout << "Shutting down PortAudio" << std::endl;
    const auto error = Pa_Terminate();
    if (error != paNoError)
    {
        std::cout << "Error during PortAudio shutdown: Error code: " << error
                  << std::endl;
    }
}

void Audio::process() {}
