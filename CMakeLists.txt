cmake_minimum_required(VERSION 3.10)

# define project name, version
project(PSEMolDyn_GroupB VERSION 0.0.1)

# let ccmake and cmake-gui offer the default build type options
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug;Release;RelWithDebInfo;MinSizeRel")

# set Release as the default build type if it is not yet set.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
            "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif(NOT CMAKE_BUILD_TYPE)

#openmp

option(OPENMP ON)

if(OPENMP)
    find_package(OpenMP)
    if (OPENMP_FOUND)
        set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
        set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    endif()
ENDIF()

#----------- libmolsim ----------------------
add_subdirectory(src)

#----------- MolSim Target ------------------
# create make target
add_executable(MolSim src/MolSim.cpp)

#Link all libmolsim code
target_link_libraries(MolSim
        PUBLIC
            libmolsim
)

# activate all compiler warnings. Clean up your code :P
# depending on the compiler different flags are used
target_compile_options(MolSim
        PRIVATE
            $<$<CXX_COMPILER_ID:GNU>:-Wall>
            # disable some spam warnings for icpc...
            $<$<CXX_COMPILER_ID:Intel>:-w3 -wd383,981,1418,1572,2259>
)

# -------------- GOOGLE TESTS --------------
enable_testing()
add_subdirectory(tests)
# ------------------------------------------

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)

include(doxygen)

option(CLUSTER "deactivate log4cxx on Linux Cluster" OFF)

if(NOT CLUSTER)
    add_compile_definitions(WITH_LOG4CXX)
endif(NOT CLUSTER)