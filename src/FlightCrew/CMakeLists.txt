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

set( SOURCES
     flightcrew.cpp
     Result.cpp
     #Validators/Opf/AuthorPresent.cpp
   )
     
file( GLOB_RECURSE TEMP Validators/*.cpp Misc/*.cpp )
list( APPEND SOURCES ${TEMP} )  

# We need to pick up the stdafx.h file
# and the headers for the linked-to libraries
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} 
                     ../ZipArchive 
                     ../BoostParts 
                     ../Xerces
                   )

link_directories ( ${PROJECT_BINARY_DIR}/lib ) 

add_library( FlightCrew ${SOURCES} )

target_link_libraries( ${PROJECT_NAME} ZipArchive BoostParts Xerces )

add_subdirectory( tests )
