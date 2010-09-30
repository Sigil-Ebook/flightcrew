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
    project( FlightCrew-gui )
else()
    project( flightcrew-gui )
endif()

#############################################################################

find_package( Qt4 4.6.0 COMPONENTS QtCore QtGui QtMain REQUIRED )

include( ${QT_USE_FILE} )

#############################################################################

file( GLOB_RECURSE RAW_SOURCES *.h *.cpp )

set( QOBJECT_HEADERS
    MainWindow.h
    )
    
set( UI_FILES   
    Form.ui 
    )
    
# Runs MOC on specifed files
qt4_wrap_cpp( MOC_FILES_CPP ${QOBJECT_HEADERS} )

# Runs UIC on specified files
qt4_wrap_ui( UI_FILES_H ${UI_FILES} )

set( ALL_SOURCES ${RAW_SOURCES} ${MOC_FILES_CPP} ${UI_FILES_H} )

#############################################################################

# Creating source groups for VS, Xcode
include( ${CMAKE_SOURCE_DIR}/cmake_extras/FileSystemSourceGroups.cmake )
create_source_groups( RAW_SOURCES )

#############################################################################

# We need to pick up the stdafx.h file
# and the headers for the linked-to libraries
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}
                     ${CMAKE_CURRENT_BINARY_DIR}
                     ${BoostParts_SOURCE_DIR}
                     ${FlightCrew_SOURCE_DIR}
                     ${XercesExtensions_SOURCE_DIR}
                     )

link_directories ( ${PROJECT_BINARY_DIR}/lib )  

add_executable( ${PROJECT_NAME} ${ALL_SOURCES} )

target_link_libraries( ${PROJECT_NAME} FlightCrew ${QT_LIBRARIES} )

#############################################################################

if( BUILD_SHARED_FC )
    add_definitions( -DFC_BUILT_AS_DLL )
endif()

#############################################################################

# "Link time code generation" flags for MSVC
# TODO: split into special cmake file
if( MSVC )
    # We'd love to use /W4 here, but there's just so much
    # noise coming from Qt it's absurd
    add_definitions( /DUNICODE /D_UNICODE )
    
    set_source_files_properties( MainWindow.cpp PROPERTIES COMPILE_DEFINITIONS /W4 )
    set_source_files_properties( main.cpp       PROPERTIES COMPILE_DEFINITIONS /W4 )
    
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:wchar_t-" )
    set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Oi /GL" ) 
    set( CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG" )

# "Print all warnings" flag for GCC
elseif( CMAKE_COMPILER_IS_GNUCXX )
    add_definitions( -Wall )
endif()