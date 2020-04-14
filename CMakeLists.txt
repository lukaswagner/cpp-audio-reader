cmake_minimum_required(VERSION 3.9)

project(audioReader C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(source_dir src)
set(include_dir include)

file(GLOB_RECURSE base_headers ${include_dir}/base/*.hpp)
file(GLOB_RECURSE base_sources ${source_dir}/base/*.cpp)

file(GLOB_RECURSE test_headers ${include_dir}/modules/test/*.hpp)
file(GLOB_RECURSE test_sources ${source_dir}/modules/test/*.cpp)
set(test_main ${source_dir}/testMain.cpp)

file(GLOB_RECURSE audio_headers ${include_dir}/modules/audio/*.hpp)
file(GLOB_RECURSE audio_sources ${source_dir}/modules/audio/*.cpp)
set(audio_main ${source_dir}/audioMain.cpp)

include(cmake/PortAudio.cmake)
include(cmake/FFTW.cmake)

include_directories(${PORTAUDIO_INCLUDE_DIR}, ${include_dir})

add_executable(test
    ${base_sources} ${base_headers}
    ${test_sources} ${test_headers}
    ${test_main})

add_executable(audioReader
    ${base_sources} ${base_headers}
    ${audio_sources} ${audio_headers}
    ${audio_main})
target_link_libraries(audioReader portaudio_static)
