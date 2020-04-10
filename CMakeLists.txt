cmake_minimum_required(VERSION 3.9)

project(audioReader CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(source_dir src)
set(include_dir include)

# set(headers
#     ${include_dir}/something.hpp)

set(sources
    ${source_dir}/main.cpp)

add_executable(audioReader ${sources} ${headers})
