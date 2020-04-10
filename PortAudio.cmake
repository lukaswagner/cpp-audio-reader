set(PORTAUDIO_INSTALLED FALSE CACHE BOOL "Check if PortAudio is installed on the system. If unchecked, specify source location.")
set(PORTAUDIO_DIR "" CACHE PATH "Source location of PortAudio.")

if(${PORTAUDIO_INSTALLED})
    find_package(portaudio)
    if(${portaudio_FOUND})
        message(STATUS "Found PortAudio installation.")
    else()
        message(FATAL_ERROR "Could not find PortAudio installation.")
    endif()
else()
    message(STATUS ${PORTAUDIO_DIR})
    if(EXISTS ${PORTAUDIO_DIR})
        add_subdirectory(${PORTAUDIO_DIR} portaudio EXCLUDE_FROM_ALL)
        set(PORTAUDIO_INCLUDE_DIR ${PORTAUDIO_DIR}/include)
    else()
        message(FATAL_ERROR "Please provide the path to the PortAudio sources.")
    endif()
endif()