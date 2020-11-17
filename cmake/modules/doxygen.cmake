# make doc_doxygen optional if someone does not have / like doxygen

# TODO: create CMake build option for the target.
option(DISABLE_DOXYGEN "disables the build of a Doxygen documentation" OFF)

# TODO: Add a custom target for building the documentation.

if(NOT DISABLE_DOXYGEN)
     find_package(Doxygen
             REQUIRED doxygen)

     SET(DOXYGEN_OUT ${PROJECT_SOURCE_DIR}/Doxyfile)

    ADD_CUSTOM_TARGET(doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating documentation using Doxygen" VERBATIM
    )
endif(NOT DISABLE_DOXYGEN)