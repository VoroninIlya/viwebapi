cmake_minimum_required(VERSION 3.22)

project(tst_viwebapi)

#include(CodeCoverage)
include(CTest)

if(PROJECT_IS_TOP_LEVEL)
    if(NOT DEFINED UNITY_ROOT_PATH)
        set(UNITY_ROOT_PATH "../unity")
    endif()

    if(NOT DEFINED GTEST_ROOT_PATH)
        set(GTEST_ROOT_PATH "../gtest")
    endif()


    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/modules/unity)
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/modules/gtest)
    # Set as executable
    add_subdirectory(${UNITY_ROOT_PATH} ${CMAKE_BINARY_DIR}/modules/unity)
    add_subdirectory(${GTEST_ROOT_PATH} ${CMAKE_BINARY_DIR}/modules/gtest)
endif()

# Add core subdir
add_subdirectory(core)

add_executable(tst_viwebapi)

enable_testing()

# Add key executable block
target_sources(tst_viwebapi PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/tests/main/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/tst_viwebapi.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/tst_viwebapinode.cpp
)

# Add key include paths
target_include_directories(tst_viwebapi PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/core/src/inc
    ${UNITY_ROOT_PATH}/src
    ${UNITY_ROOT_PATH}/extras/fixture/src
    ${UNITY_ROOT_PATH}/extras/memory/src
    ${GTEST_ROOT_PATH}/googlemock/include
)

# Compilation definition information
target_compile_definitions(tst_viwebapi PUBLIC
    #WIN32
    #_DEBUG
    #CONSOLE
)

# Compiler options
target_compile_options(tst_viwebapi PUBLIC
    -g
    -fprofile-arcs 
    -ftest-coverage
    -Wall
    -Wextra
    -Wpedantic
)

target_link_libraries(
  tst_viwebapi PUBLIC viwebapi unity gmock -lgcov -fprofile-arcs -ftest-coverage -pthread)

add_test(NAME ViWebApiTest COMMAND tst_viwebapi "--gtest_filter=ViWebApiTest.*")
add_test(NAME ViWebApiNodeTest COMMAND tst_viwebapi "--gtest_filter=ViWebApiNodeTest.*")
