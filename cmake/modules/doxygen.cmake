 # make doc_doxygen optional if someone does not have / like doxygen

 # TODO: create CMake build option for the target.
 option(DISABLE_DOXYGEN "disables the build of a Doxygen documentation" OFF)

 # TODO: Add a custom target for building the documentation.

 #Add target to build documents from visual studio.
 #set(DOXYGEN_INPUT Doxyfile)
 #set the output directory of the documentation
 set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/doxys_documentation)
 # sanity check...
 #message("Doxygen Output ${DOXYGEN_OUTPUT_DIR}")

 if(NOT DISABLE_DOXYGEN)
     ADD_CUSTOM_TARGET(doc_doxygen
             COMMAND ${CMAKE_COMMAND} -E make_directory ${DOXYGEN_OUTPUT_DIR}
             ${DOXYGEN_EXECUTABLE} Doxyfile
             #WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
             VERBATIM
             )
 endif(NOT DISABLE_DOXYGEN) custom target for building the documentation.