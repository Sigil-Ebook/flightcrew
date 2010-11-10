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
set( FLIGHTCREW_MINOR_VERSION 7 )
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
# create exes that can run on 10.5+
set( CMAKE_OSX_DEPLOYMENT_TARGET "10.5" )

# Build fails with the 10.4 SDK, so we'll just have to use
# the 10.5 one and hope for the best.
set( CMAKE_OSX_SYSROOT "/Developer/SDKs/MacOSX10.5.sdk" )

# Universal builds for mac
set( CMAKE_OSX_ARCHITECTURES "i386;x86_64" )

# The parsing order is significant!
add_subdirectory( src/BoostParts )
add_subdirectory( src/Xerces )
add_subdirectory( src/XercesExtensions )
add_subdirectory( src/zlib )
add_subdirectory( src/zipios )
add_subdirectory( src/googlemock )
add_subdirectory( src/FlightCrew )
add_subdirectory( src/FlightCrew-cli )

if( NOT SKIP_FC_GUI )
    add_subdirectory( src/FlightCrew-gui )
endif()
