cmake_minimum_required(VERSION 3.2) 

project(LFU_cache LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O2 -Wall")
set(CMAKE_BUILD_TYPE RELEASE)

add_subdirectory(lfu_cache)
add_subdirectory(perfect_cache)
add_subdirectory(test)
