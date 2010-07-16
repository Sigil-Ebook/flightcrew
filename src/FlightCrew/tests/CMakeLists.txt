########################################################
#  
#  This is a CMake configuration file.
#  To use it you need CMake which can be 
#  downloaded from here: 
#    http://www.cmake.org/cmake/resources/software.html
#
#########################################################

cmake_minimum_required( VERSION 2.8 ) 

project( fc_tests ) 
     
file( GLOB_RECURSE SOURCES *.cpp )

#############################################################################

# We need to pick up the stdafx.h file
# and the headers for the linked-to libraries
include_directories( ../../ZipArchive 
                     ../../BoostParts 
                     ../../Xerces 
                     ../../googlemock/include
                     ../../googlemock/gtest/include
                   )

link_directories ( ${PROJECT_BINARY_DIR}/lib ) 

#############################################################################

add_executable( ${PROJECT_NAME} ${SOURCES} )

target_link_libraries( ${PROJECT_NAME} FlightCrew gmock )

#############################################################################

# The test executable expects a "test_data" dir in its working directory
add_custom_target(  copy_test_data ALL 
                    COMMAND cmake -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/test_data 
                                                    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_data )
