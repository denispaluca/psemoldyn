cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE MY_SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        # header don't need to be included but this might be necessary for some IDEs
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx"
        # header don't need to be included but this might be necessary for some IDEs
        "${CMAKE_CURRENT_SOURCE_DIR}/*.hxx"
        )

list(REMOVE_ITEM MY_SRC ${CMAKE_CURRENT_SOURCE_DIR}/MolSim.cpp)
add_library(libmolsim STATIC ${MY_SRC})

# set cxx standard. You may raise this if you want.
target_compile_features(libmolsim
        PRIVATE
            cxx_std_14
        )

target_include_directories(libmolsim
        PUBLIC
            ${CMAKE_SOURCE_DIR}/libs/libxsd
            ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(libmolsim
        # stuff that is used in headers and source files
        PUBLIC
            xerces-c
        )

if(NOT CLUSTER)
    target_link_libraries(libmolsim
            #----------- include log4cxx-----------
            PRIVATE
                log4cxx
            )
endif(NOT CLUSTER)
