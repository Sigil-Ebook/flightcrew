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

set( CMAKE_DEBUG_POSTFIX "d" )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib )
set( PACKAGE_DIRECTORY ${PROJECT_BINARY_DIR}/package )

set( FLIGHTCREW_MAJOR_VERSION 0 )
set( FLIGHTCREW_MINOR_VERSION 9 )
set( FLIGHTCREW_REVISION_VERSION 1 )
set( FLIGHTCREW_FULL_VERSION ${FLIGHTCREW_MAJOR_VERSION}.${FLIGHTCREW_MINOR_VERSION}.${FLIGHTCREW_REVISION_VERSION} )

# Check if platform is 64 bit
if( NOT APPLE )
   if( CMAKE_SIZEOF_VOID_P EQUAL 4 )
     set( 64_BIT_PLATFORM 0 )
   else()
     set( 64_BIT_PLATFORM 1 )
   endif()
endif()

# We need this to make sure g++ and the linker
# create exes that can run on 10.9+
set( CMAKE_OSX_DEPLOYMENT_TARGET "10.9" )

# 10.9 is the required minimum OS X version.
# set( CMAKE_OSX_SYSROOT "/Developer/SDKs/MacOSX10.9.sdk" )
# Universal builds for mac
# set( CMAKE_OSX_ARCHITECTURES "i386;x86_64" )


# The parsing order is significant!

add_subdirectory( src/BoostParts )
# Set these so zipios doesn't complain.
set( Boost_DATE_TIME_LIBRARY 1 )
set( Boost_FILESYSTEM_LIBRARY 1 )
set( Boost_PROGRAM_OPTIONS_LIBRARY 1 )
set( Boost_REGEX_LIBRARY 1 )
set( Boost_SYSTEM_LIBRARY 1 )
set( Boost_THREAD_LIBRARY 1 )
set( BOOST_LIBS BoostParts )
set( BOOST_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src/BoostParts )

add_subdirectory( src/Xerces )
set( XERCES_LIBRARIES Xerces )
set( XERCES_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src/Xerces )

add_subdirectory( src/XercesExtensions )
set( XERCESEXTENSIONS_LIBRARIES XercesExtensions )
set( XERCESEXTENSIONS_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src/XercesExtensions )

add_subdirectory( src/zlib )
add_subdirectory( src/zipios )
if( NOT MINGW )
    add_subdirectory( src/googlemock )
endif()

add_subdirectory( src/FlightCrew )
set( FLIGHTCREW_LIBRARIES FlightCrew )
set( FLIGHTCREW_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src/FlightCrew )

add_subdirectory( src/FlightCrew-cli )

if( NOT SKIP_FC_GUI )
    add_subdirectory( src/FlightCrew-gui )
endif()

if( NOT SKIP_FC_PLUGIN )
    add_subdirectory( src/FlightCrew-plugin )
endif()

