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

set( SOURCES
     ../../googlemock/src/gmock_main.cc
     )
     
# We need to pick up the stdafx.h file
# and the headers for the linked-to libraries
include_directories( ../../ZipArchive 
                     ../../BoostParts 
                     ../../Xerces 
                     ../../googlemock/include
                     ../../googlemock/gtest/include
                   )

link_directories ( ${PROJECT_BINARY_DIR}/lib ) 

target_link_libraries( ${PROJECT_NAME} FlightCrew )

add_executable( ${PROJECT_NAME} ${SOURCES} )
