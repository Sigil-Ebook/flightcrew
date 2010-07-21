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
                     ../../XercesExtensions 
                     ../../googlemock/include
                     ../../googlemock/gtest/include
                   )

link_directories ( ${PROJECT_BINARY_DIR}/lib ) 

#############################################################################

add_executable( ${PROJECT_NAME} ${SOURCES} )

target_link_libraries( ${PROJECT_NAME} FlightCrew gmock )

#############################################################################

if( MSVC )
	add_definitions( /DUNICODE /D_UNICODE )
    # The /Zc:wchar_t- flag can't go into add_definitions
    # because the RC compiler picks it up too and it provokes a name clash
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:wchar_t-")
	set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Oi /GL" ) 
	set( CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG" )
endif()

#############################################################################

# The test executable expects a "test_data" dir in its working directory
add_custom_target(  copy_test_data ALL 
                    COMMAND cmake -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/test_data 
                                                    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_data )


