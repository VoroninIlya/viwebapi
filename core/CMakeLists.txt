cmake_minimum_required(VERSION 3.22)

project(viwebapi)

# Debug message
message("Entering ${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt")

# Register core library
add_library(viwebapi INTERFACE)

target_sources(viwebapi PUBLIC )

target_include_directories(viwebapi INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/inc)
