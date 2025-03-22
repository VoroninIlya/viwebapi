cmake_minimum_required(VERSION 3.22)

project(tst_viwebapi)

#include(CodeCoverage)
include(CTest)

if(PROJECT_IS_TOP_LEVEL)
# Set as executable
add_subdirectory(${UNITY_ROOT_PATH} ${${EXECUTABLE}_BINARY_DIR}/modules/gtest)
endif()

# Add core subdir
add_subdirectory(core)

add_executable(tst_viwebapi)
enable_testing()

# Add key executable block
target_sources(tst_viwebapi PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/tests/main/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/tst_viwebapi.cpp
)

# Add key include paths
target_include_directories(tst_viwebapi PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/core/src/inc
    ${UNITY_ROOT_PATH}/src
    ${UNITY_ROOT_PATH}/extras/fixture/src
    ${UNITY_ROOT_PATH}/extras/memory/src
)

# Compilation definition information
target_compile_definitions(tst_viwebapi PUBLIC
    WIN32
    _DEBUG
    CONSOLE
)

# Compiler options
target_compile_options(tst_viwebapi PRIVATE
    -g
    --coverage
    -Wall
    -Wextra
    -Wpedantic
)

target_link_libraries(
  tst_viwebapi viwebapi unity -g -coverage -lgcov)

#add_test(NAME VIHCSR04_Init COMMAND tst_vibuttonctrl "--gtest_filter=VIHCSR04_Init.*")
