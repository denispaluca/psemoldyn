cmake_minimum_required(VERSION 3.10)

project(Tests)
add_subdirectory(lib EXCLUDE_FROM_ALL)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
file(GLOB_RECURSE TEST_SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        # header don't need to be included but this might be necessary for some IDEs
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
        )

add_executable(Tests_run ${TEST_SRC})
set_target_properties(Tests_run PROPERTIES EXCLUDE_FROM_ALL 1)

target_link_libraries(Tests_run gtest gtest_main)
target_link_libraries(Tests_run libmolsim)

add_test(NAME Tests_run COMMAND Tests_run)