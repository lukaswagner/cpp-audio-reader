#include <iostream>

#include <portaudio.h>

int main(int argc, char const *argv[])
{
    const auto info = Pa_GetVersionInfo();
    std::cout << "Using " << info->versionText << std::endl;
    return 0;
}
