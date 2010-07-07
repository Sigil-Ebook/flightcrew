########################################################
#  
#  This is a CMake configuration file.
#  To use it you need CMake which can be 
#  downloaded from here: 
#    http://www.cmake.org/cmake/resources/software.html
#
#########################################################

cmake_minimum_required( VERSION 2.8 ) 

project( Xerces )

set( SOURCES )

# Using the provided folder_path, recursively adds
# all the CPP, HPP and H source files to the SOURCES list.
macro( add_to_sources folder_path )
    file( GLOB_RECURSE TEMP ${folder_path}/*.cpp ${folder_path}/*.h ${folder_path}/*.hpp )   
    list( LENGTH SOURCES len )    
    
    if ( ${len} EQUAL 0 )
        set( SOURCES ${TEMP} )        
    else()
        list( APPEND SOURCES ${TEMP} )
    endif()
endmacro()

# Using the provided folder_path, adds
# all the CPP, HPP and H source files to the SOURCES list.
# Only the folder_path is looked at, not the child folders. 
macro( add_to_sources_no_rec folder_path )
    file( GLOB TEMP ${folder_path}/*.cpp ${folder_path}/*.h ${folder_path}/*.hpp )   
    list( LENGTH SOURCES len )    
    
    if ( ${len} EQUAL 0 )
        set( SOURCES ${TEMP} )        
    else()
        list( APPEND SOURCES ${TEMP} )
    endif()
endmacro()

add_to_sources( xercesc/dom )
add_to_sources( xercesc/framework )
add_to_sources( xercesc/internal )
add_to_sources( xercesc/parsers )
add_to_sources( xercesc/sax )
add_to_sources( xercesc/sax2 )
add_to_sources( xercesc/validators )
add_to_sources( xercesc/xinclude )

add_to_sources( xercesc/util/MsgLoaders/InMemory )

add_to_sources_no_rec( xercesc/util )

# There are two "autoconf" config files: one for Unix systems,
# and one for MSVC. The one for Unix systems is created by running
# "./configure", but we're CMake based so we use a sensible,
# configure generated file that we then tweak by hand.
if( MSVC )
    list( REMOVE_ITEM SOURCES xercesc/util/Xerces_autoconf_config.hpp )
else()
    list( REMOVE_ITEM SOURCES xercesc/util/Xerces_autoconf_config.msvc.hpp )
endif()

#list( APPEND SOURCES 
#        xercesc/util/NetAccessors/BinHTTPInputStreamCommon.cpp
#        xercesc/util/NetAccessors/BinHTTPInputStreamCommon.hpp )

if( MSVC )
    add_to_sources( xercesc/util/Transcoders/Win32 )
    #add_to_sources( xercesc/util/NetAccessors/WinSock )
    
    list( APPEND SOURCES
        xercesc/util/FileManagers/WindowsFileMgr.hpp
        xercesc/util/FileManagers/WindowsFileMgr.cpp
        xercesc/util/MutexManagers/WindowsMutexMgr.hpp
        xercesc/util/MutexManagers/WindowsMutexMgr.cpp )
else()
    #add_to_sources( xercesc/util/Transcoders/Iconv )
    add_to_sources( xercesc/util/Transcoders/IconvGNU )
    #add_to_sources( xercesc/util/NetAccessors/Socket )
    
    list( APPEND SOURCES
        xercesc/util/FileManagers/PosixFileMgr.hpp
        xercesc/util/FileManagers/PosixFileMgr.cpp
        xercesc/util/MutexManagers/PosixMutexMgr.hpp
        xercesc/util/MutexManagers/PosixMutexMgr.cpp  )
endif()
        
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

add_library( Xerces ${SOURCES} ) 

add_definitions( -DXERCES_STATIC_LIBRARY
                 -DXERCES_BUILDING_LIBRARY
                 -DXERCES_USE_MSGLOADER_INMEMORY
                 #-DHAVE_STRICMP
                 #-DHAVE_STRNICMP
                 -DHAVE_LIMITS_H
                 -DHAVE_SYS_TIMEB_H
                 -DHAVE_FTIME
                 -DHAVE_WCSUPR
                 -DHAVE_WCSLWR
                 -DHAVE_WCSICMP
                 -DHAVE_WCSNICMP )

if( MSVC )
	add_definitions( -DUNICODE -D_UNICODE )
    add_definitions( -D_CRT_SECURE_NO_DEPRECATE
                     -DXERCES_PATH_DELIMITER_BACKSLASH
                     -DXERCES_USE_TRANSCODER_WINDOWS
                     -DXERCES_USE_FILEMGR_WINDOWS   
                     -DXERCES_USE_MUTEXMGR_WINDOWS
                     #-DXERCES_USE_NETACCESSOR_WINSOCK 
                   )
                     
    # xerces wants to disable these warnings
    add_definitions( /wd4996 )
    add_definitions( /wd4355 )
    
    set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Oi /GL" ) 
	set_target_properties( Xerces PROPERTIES STATIC_LIBRARY_FLAGS "/LTCG" )
    
else()
    add_definitions( -DXERCES_USE_FILEMGR_POSIX
                     #-DXERCES_USE_TRANSCODER_ICONV
                     -DXERCES_USE_TRANSCODER_GNUICONV
                     -DXERCES_USE_MUTEXMGR_POSIX 
                     #-DXERCES_USE_NETACCESSOR_SOCKET 
                   )                     
endif()

 



