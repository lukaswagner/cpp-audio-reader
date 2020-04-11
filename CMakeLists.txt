cmake_minimum_required(VERSION 3.9)

project(audioReader C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(source_dir src)
set(include_dir include)

set(headers
    ${include_dir}/base/module.hpp
    ${include_dir}/base/input.hpp
    ${include_dir}/base/output.hpp
    ${include_dir}/base/inputOutput.hpp
    ${include_dir}/audio.hpp)

set(sources
    ${source_dir}/base/input.cpp
    ${source_dir}/base/output.cpp
    ${source_dir}/main.cpp
    ${source_dir}/audio.cpp)

include(PortAudio.cmake)

include_directories(${PORTAUDIO_INCLUDE_DIR}, ${include_dir})
add_executable(audioReader ${sources} ${headers})
target_link_libraries(audioReader portaudio_static)
