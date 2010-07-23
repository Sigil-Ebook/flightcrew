########################################################
#  
#  This is a CMake configuration file.
#  To use it you need CMake which can be 
#  downloaded from here: 
#    http://www.cmake.org/cmake/resources/software.html
#
#########################################################

cmake_minimum_required( VERSION 2.8 ) 

project( FlightCrew )

file( GLOB_RECURSE SOURCES *.h *.cpp )

# The test sources are a part of a different target, so we remove them
file( GLOB_RECURSE to_remove tests/*.h tests/*.cpp )
list( REMOVE_ITEM SOURCES ${to_remove} )

#############################################################################

# Creating source groups for VS, Xcode
include( ${CMAKE_SOURCE_DIR}/cmake_extras/FileSystemSourceGroups.cmake )
create_source_groups( SOURCES )

#############################################################################

set( PCH_NAME stdafx )

# stdafx.cpp is compiled separately as a PCH
file( GLOB to_remove ${PCH_NAME}.cpp )
list( REMOVE_ITEM SOURCES ${to_remove} )

#############################################################################

# creating PCH's for MSVC and GCC on Linux
include( ${CMAKE_SOURCE_DIR}/cmake_extras/CustomPCH.cmake )
set( ALL_INCLUDES ${BoostParts_SOURCE_DIR}
                  ${Xerces_SOURCE_DIR}
                  ${ZipArchive_SOURCE_DIR} )
				 
set( GCC_PCH_TARGET gccPCH_fc )

precompiled_header( SOURCES ALL_INCLUDES ${GCC_PCH_TARGET} ${PCH_NAME} )

#############################################################################

# We need to pick up the stdafx.h file (current source dir),
# the stdafx.h.gch file (current binary dir)
# and the headers for the linked-to libraries
include_directories( ${CMAKE_CURRENT_BINARY_DIR}
                     ${CMAKE_CURRENT_SOURCE_DIR}
                     ../ZipArchive 
                     ../BoostParts 
                     ../Xerces
                     ../XercesExtensions
                   )

link_directories ( ${PROJECT_BINARY_DIR}/lib ) 

add_library( ${PROJECT_NAME} ${SOURCES} )

target_link_libraries( ${PROJECT_NAME} ZipArchive BoostParts XercesExtensions )

#############################################################################

# "Link time code generation" flags for MSVC
# TODO: split into special cmake file
if( MSVC )
    add_definitions( /DUNICODE /D_UNICODE )
    # The /Zc:wchar_t- flag can't go into add_definitions
    # because the RC compiler picks it up too and it provokes a name clash
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:wchar_t-")
	set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Oi /GL" ) 
	set_target_properties( ${PROJECT_NAME} PROPERTIES STATIC_LIBRARY_FLAGS "/LTCG" )

# "Print all warnings" flag for GCC
elseif( CMAKE_COMPILER_IS_GNUCXX )
    add_definitions( -Wall )

    # Make sure the PCH is built for GCC
    add_dependencies( ${PROJECT_NAME} ${GCC_PCH_TARGET} )
endif()

# needed for correct Xerces header inclusion
add_definitions( -DXERCES_STATIC_LIBRARY )

#############################################################################

add_subdirectory( tests )
