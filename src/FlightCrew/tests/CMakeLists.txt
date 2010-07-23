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
     
# Normally we wouldn't include the xml files in the SOURCES just
# to get nice source groups from the create_source_groups() macro,
# but a CMake bug is forcing us to do so. It refuses to work if we 
# glob for xml files separately and then run create_source_groups()
# again... putting them in the SOURCES fixes this, and they're not
# doing any realy harm. CMake is smart enough to not forward them to the compiler.
file( GLOB_RECURSE SOURCES *.cpp *.xml )

# Creating source groups for VS, Xcode
include( ${CMAKE_SOURCE_DIR}/cmake_extras/FileSystemSourceGroups.cmake )
create_source_groups( SOURCES )

#############################################################################

# stdafx.cpp is compiled separately as a PCH
file( GLOB to_remove stdafx.cpp )
list( REMOVE_ITEM SOURCES ${to_remove} )

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

# creating PCH's for MSVC and GCC on Linux
include( ${CMAKE_SOURCE_DIR}/cmake_extras/CustomPCH.cmake )
set( ALL_INCLUDES ${gtest_SOURCE_DIR}/include )

set( GCC_PCH_TARGET gccPCH_tests )

precompiled_header( SOURCES ALL_INCLUDES ${GCC_PCH_TARGET} )

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
	
elseif( CMAKE_COMPILER_IS_GNUCXX )
	# Make sure the PCH is built for GCC
    add_dependencies( ${PROJECT_NAME} ${GCC_PCH_TARGET} )
endif()

# needed for correct Xerces header inclusion
add_definitions( -DXERCES_STATIC_LIBRARY )

#############################################################################

# The test executable expects a "test_data" dir in its working directory.
# MSVC creates the test executable in a Release or Debug subdir (depending
# on the build configuration) so we copy the data there in this case.
add_custom_target( copy_test_data ALL )

if ( NOT MSVC )
	add_custom_command( TARGET copy_test_data POST_BUILD 
						COMMAND cmake -E copy_directory 
						${CMAKE_CURRENT_SOURCE_DIR}/test_data 
					 	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_data )
else()
	add_custom_command( TARGET copy_test_data POST_BUILD 
						COMMAND cmake -E copy_directory 
						${CMAKE_CURRENT_SOURCE_DIR}/test_data 
					 	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/test_data )
						
	add_custom_command( TARGET copy_test_data POST_BUILD
						COMMAND cmake -E copy_directory 
						${CMAKE_CURRENT_SOURCE_DIR}/test_data 
					 	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/test_data )
endif()


