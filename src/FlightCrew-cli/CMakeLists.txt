########################################################
#  
#  This is a CMake configuration file.
#  To use it you need CMake which can be 
#  downloaded from here: 
#    http://www.cmake.org/cmake/resources/software.html
#
#########################################################

cmake_minimum_required( VERSION 2.8 ) 

# We use the lower case name
# on UNIX systems other than Mac OS X
if ( WIN32 OR APPLE )
    project( FlightCrew-cli )
else()
    project( flightcrew-cli )
endif()

file( GLOB_RECURSE SOURCES *.cpp *.h ) 

#############################################################################

# Creating source groups for VS, Xcode
include( ${CMAKE_SOURCE_DIR}/cmake_extras/FileSystemSourceGroups.cmake )
create_source_groups( SOURCES )

#############################################################################

# We need to pick up the stdafx.h file
# and the headers for the linked-to libraries
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}
                     ${BoostParts_SOURCE_DIR}
                     ${FlightCrew_SOURCE_DIR}
                     ${XercesExtensions_SOURCE_DIR}
                     )

add_executable( ${PROJECT_NAME} ${SOURCES} )

target_link_libraries( ${PROJECT_NAME} FlightCrew )

#############################################################################

if( BUILD_SHARED_FC )
    add_definitions( -DFC_BUILT_AS_DLL )
endif()

#############################################################################

# "Link time code generation" flags for MSVC
# TODO: split into special cmake file
if( MSVC )
    add_definitions( /DUNICODE /D_UNICODE /W4 )
    
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:wchar_t- /MP" )
    set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Oi /GL" ) 
    set( CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG" )

elseif( MINGW )
    add_definitions( -Wall )
    set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static" )

# "Print all warnings" flag for GCC
elseif( CMAKE_COMPILER_IS_GNUCXX )
    add_definitions( -Wall )
endif()

set_source_files_properties( main.cpp PROPERTIES COMPILE_DEFINITIONS FLIGHTCREW_FULL_VERSION="${FLIGHTCREW_FULL_VERSION}" )

#############################################################################

# You can change the install location by 
# running cmake like this:
#
#   cmake -DCMAKE_INSTALL_PREFIX=/new/install/prefix
#
# By default, the prefix is "/usr/local"
# 
if( UNIX AND NOT APPLE )
    install( TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin )
endif()
