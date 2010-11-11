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
file( GLOB_RECURSE TEST_SOURCES *.cpp *.xml )

# Creating source groups for VS, Xcode
include( ${CMAKE_SOURCE_DIR}/cmake_extras/FileSystemSourceGroups.cmake )
create_source_groups( TEST_SOURCES )

#############################################################################

set( PCH_NAME stdafx_tests )

# stdafx.cpp is compiled separately as a PCH
file( GLOB to_remove ${PCH_NAME}.cpp )
list( REMOVE_ITEM TEST_SOURCES ${to_remove} )

#############################################################################

# We need to pick up the stdafx.h file (current source dir),
# the stdafx.h.gch file (current binary dir)
# and the headers for the linked-to libraries

# Include_directories is ADDITIVE on folder recursion!
# That means that subdirs inherit the include_directories of their parents.
# So techincally we don't need to include Xerces etc.
include_directories( ${CMAKE_CURRENT_BINARY_DIR} 
                     ${CMAKE_CURRENT_SOURCE_DIR} 
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
set( ALL_INCLUDES ${gtest_SOURCE_DIR}/include ${BoostParts_SOURCE_DIR} )

set( GCC_PCH_TARGET gccPCH_tests )

precompiled_header( TEST_SOURCES ALL_INCLUDES ${GCC_PCH_TARGET} ${PCH_NAME} )

#############################################################################

add_executable( ${PROJECT_NAME} ${TEST_SOURCES} )

target_link_libraries( ${PROJECT_NAME} FlightCrew gmock )

#############################################################################

# Xcode PCH support. Has to come after the target is created.              
if( APPLE )                   
    set_target_properties(
        ${PROJECT_NAME} 
        PROPERTIES
        XCODE_ATTRIBUTE_GCC_PREFIX_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/${PCH_NAME}.h"
        XCODE_ATTRIBUTE_GCC_PRECOMPILE_PREFIX_HEADER "YES"
    )
endif() 

#############################################################################

if( MSVC )
    add_definitions( /DUNICODE /D_UNICODE /W4 )
    
    # This warning is present only at the highest warning level (/W4)
    # and is routinely disabled because it complains about valid 
    # constructs like "while (true)"
    add_definitions( /wd4127 )
    
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
if ( NOT MSVC_IDE )
    add_custom_target( copy_test_data 
                       COMMAND cmake -E copy_directory 
                       ${CMAKE_CURRENT_SOURCE_DIR}/test_data 
                       ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_data )
else()
    # MSVC_IDE creates the test executable in a Release or Debug subdir (depending
    # on the build configuration) so we copy the data there in this case.
    add_custom_target( copy_test_data 
                       COMMAND cmake -E copy_directory 
                       ${CMAKE_CURRENT_SOURCE_DIR}/test_data 
                       ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/test_data                       
                       COMMAND cmake -E copy_directory 
                       ${CMAKE_CURRENT_SOURCE_DIR}/test_data 
                       ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/test_data )
endif()

add_dependencies( ${PROJECT_NAME} copy_test_data )

