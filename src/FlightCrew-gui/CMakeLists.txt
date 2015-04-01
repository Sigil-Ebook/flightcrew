########################################################
#  
#  This is a CMake configuration file.
#  To use it you need CMake which can be 
#  downloaded from here: 
#    http://www.cmake.org/cmake/resources/software.html
#
#########################################################

cmake_minimum_required( VERSION 2.8 ) 

if(POLICY CMP0020)
    cmake_policy(SET CMP0020 OLD)
endif()
if(POLICY CMP0043)
    cmake_policy(SET CMP0043 OLD)
endif()

# We use the lower case name
# on UNIX systems other than Mac OS X
if ( WIN32 OR APPLE )
    project( FlightCrew-gui )
else()
    project( flightcrew-gui )
endif()

#############################################################################

find_package(Qt5 5.4 COMPONENTS Core Widgets Gui Network)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

get_target_property(QMAKE_EXECUTABLE Qt5::qmake LOCATION)
function(QUERY_QMAKE VAR RESULT)
    exec_program(${QMAKE_EXECUTABLE} ARGS "-query ${VAR}" RETURN_VALUE return_code OUTPUT_VARIABLE output )
    if(NOT return_code)
        file(TO_CMAKE_PATH "${output}" output)
        set(${RESULT} ${output} PARENT_SCOPE)
    endif(NOT return_code)
endfunction(QUERY_QMAKE)

#############################################################################

file( GLOB_RECURSE RAW_SOURCES *.h *.cpp )

set( QOBJECT_HEADERS
    MainWindow.h
    UpdateChecker.h
    )
    
set( UI_FILES   
    Form.ui 
    )
    
# Runs UIC on specified files
qt5_wrap_ui( UI_FILES_H ${UI_FILES} )

set( ALL_SOURCES ${RAW_SOURCES} ${MOC_FILES_CPP} ${UI_FILES_H} )

#############################################################################

# Apple bundle configuration
if( APPLE )
    # Copy the PLIST file...
    exec_program( "cp ${PROJECT_SOURCE_DIR}/resources/mac/MacOSXBundleInfo.plist ${PROJECT_BINARY_DIR}")
    
    # ...and set the FlightCrew version string
    exec_program( "sed -i -e 's/FCVERSION/${FLIGHTCREW_FULL_VERSION}/g' ${PROJECT_BINARY_DIR}/MacOSXBundleInfo.plist")
endif()

#############################################################################

# Creating source groups for VS, Xcode
include( ${CMAKE_SOURCE_DIR}/cmake_extras/FileSystemSourceGroups.cmake )
create_source_groups( RAW_SOURCES )

#############################################################################

# We need to pick up the stdafx.h file
# and the headers for the linked-to libraries
include_directories( BEFORE
                     ${CMAKE_CURRENT_SOURCE_DIR}
                     ${CMAKE_CURRENT_BINARY_DIR}
                     ${BoostParts_SOURCE_DIR}
                     ${FlightCrew_SOURCE_DIR}
                     ${XercesExtensions_SOURCE_DIR}
                     )

#############################################################################

# We make bundles for Mac OS X
if ( APPLE )
    add_executable( ${PROJECT_NAME} MACOSX_BUNDLE ${ALL_SOURCES} )
    set_target_properties( ${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${PROJECT_BINARY_DIR}/MacOSXBundleInfo.plist )
# ...and a normal executable for everything else.
else()
    add_executable( ${PROJECT_NAME} WIN32 ${ALL_SOURCES} )
endif()


if (MSVC)
    set(QT_MAIN Qt5::WinMain)
endif()

# target_link_libraries( ${PROJECT_NAME} FlightCrew ${QT_LIBRARIES} )

target_link_libraries( ${PROJECT_NAME} ${QT_MAIN} ${FLIGHTCREW_LIBRARIES} )
qt5_use_modules(${PROJECT_NAME} Widgets Core Gui Network)


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
    
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:wchar_t- /MP" )
    set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Oi /GL" ) 
    set( CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG" )

# "Print all warnings" flag for GCC
elseif( CMAKE_COMPILER_IS_GNUCXX )
    add_definitions( -Wall )
endif()

set_source_files_properties( MainWindow.cpp PROPERTIES COMPILE_DEFINITIONS FLIGHTCREW_FULL_VERSION="${FLIGHTCREW_FULL_VERSION}" )
set_source_files_properties( UpdateChecker.cpp PROPERTIES COMPILE_DEFINITIONS FLIGHTCREW_FULL_VERSION="${FLIGHTCREW_FULL_VERSION}" )

#############################################################################

# For Mac, add frameworks and make a DMG
if( APPLE )
    if(CMAKE_GENERATOR STREQUAL Xcode)
        set( WORK_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release" )
    else()
        set( WORK_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}" )
    endif()

    add_custom_target(  addframeworks ALL 
                        COMMAND macdeployqt FlightCrew-gui.app
                        WORKING_DIRECTORY ${WORK_DIR}
                        DEPENDS ${PROJECT_NAME} )

    add_custom_target(  makedmg 
                        COMMAND macdeployqt FlightCrew-gui.app -dmg -no-plugins
                        WORKING_DIRECTORY ${WORK_DIR}
                        DEPENDS addframeworks )
                
# For Linux and Windows, provide binary installers.
# For this to work on Linux, InstallJammer needs to be installed and on the system path.
# For this to work on Windows, Inno Setup's iscc compiler needs to be installed and on the system path.
else()
    set( TEMP_PACKAGE_DIR ${CMAKE_BINARY_DIR}/temp_folder )
    set( MAIN_PACKAGE_DIR ${TEMP_PACKAGE_DIR}/FlightCrew )
    set( OUTPUT_PACKAGE_DIR ${CMAKE_BINARY_DIR}/installer )
    
    # MPI (InstallJammer) file will need to be copied to this location
    set( MPI_LOCATION ${CMAKE_BINARY_DIR}/temp_folder/FlightCrew.mpi )
    
    # ISS conf file for the Inno Setup compiler
    # We first create a CMake configured version of the ISS file,
    # and then we copy it to the temp folder every time we need to build the installer.
    set( ISS_MAIN_LOCATION ${CMAKE_SOURCE_DIR}/installer/FlightCrew.iss  )
    Set( ISS_OC_LOCATION ${CMAKE_SOURCE_DIR}/OpenCandy/FlightCrewOC.iss  )
    set( ISS_CONFIGURED_LOCATION ${CMAKE_BINARY_DIR}/FlightCrew_configured.iss )
    set( ISS_TEMP_LOCATION ${CMAKE_BINARY_DIR}/temp_folder/FlightCrew_configured.iss )

    if ( 64_BIT_PLATFORM )
        # Used in the ISS CMake configuration
        set( ISS_ARCH "x64" )
        set( ISS_SETUP_FILENAME_PLATFORM "-x64" )
    endif()
    
    # This is used to build OpenCandy installers. You can't build them
    # from the source repo and you shouldn't want to either. By default,
    # vanilla installers are built. You want the vanillas.
    if ( EXISTS ${ISS_OC_LOCATION} )
        set( OC_INSTALLERS TRUE )
    endif()
    
    # Creates a copy of the ISS file in ${ISS_CONFIGURED_LOCATION} and then configures it 
    if ( OC_INSTALLERS )
        set( LICENSE_LOCATION ${CMAKE_SOURCE_DIR}/OpenCandy/win_installer_note.txt )
        configure_file( ${ISS_OC_LOCATION} ${ISS_CONFIGURED_LOCATION} ) 
    else()
        set( LICENSE_LOCATION ${CMAKE_SOURCE_DIR}/installer/win_installer_note.txt )
        configure_file( ${ISS_MAIN_LOCATION} ${ISS_CONFIGURED_LOCATION} ) 
    endif()
    
    # Specify platform var for installjammer
    if ( WIN32 )
        set( PLATFORM "Windows" )
    else()
        if ( 64_BIT_PLATFORM )
            set( PLATFORM "Linux-x86_64" )
        else()
            set( PLATFORM "Linux-x86" )
        endif()
    endif()
    
    # We use Inno for the Windows installers and InstallJammer for the Linux ones
    if ( WIN32 )
        # Run Inno Setup's iscc compiler (*AFTER* all the PRE_BUILD custom commands execute)
        add_custom_target(  makeinstaller 
                            COMMAND cmake -E echo "For this to work, Inno Setup's iscc compiler needs to be installed and on the system path."
                            COMMAND iscc ${ISS_TEMP_LOCATION} )
    else()
        # Run InstallJammer (*AFTER* all the PRE_BUILD custom commands execute)
        add_custom_target(  makeinstaller 
                            COMMAND cmake -E echo "For this to work, InstallJammer needs to be installed and on the system path."
                            COMMAND installjammer   -DBaseDir ${MAIN_PACKAGE_DIR}  
                                                    -DFCMajorVersion ${FLIGHTCREW_MAJOR_VERSION}
                                                    -DFCMinorVersion ${FLIGHTCREW_MINOR_VERSION}
                                                    -DFCRevisionVersion ${FLIGHTCREW_REVISION_VERSION}
                                                    --platform ${PLATFORM}
                                                    --output-dir ${OUTPUT_PACKAGE_DIR}
                                                    --build-for-release
                                                    --verbose   
                                                    --build ${MPI_LOCATION} )
    endif()

    # We need to copy the files that will be used to make the installer to
    # a temporary directory. On the MSVC compiler the PRE_BUILD custom commands
    # can be added directly, but on other generators we need an intermediate target
    # since the PRE_BUILD condition is not supported. Using the intermediate for
    # MSVC makes it unnecessarily recompile that target every time the project is built.
    # So we use the direct way on MSVC, and the intemediate way for other generators.
    if( MSVC_IDE )
        set( TARGET_FOR_COPY makeinstaller )
        add_dependencies( makeinstaller ${PROJECT_NAME} )
    else()
        set( TARGET_FOR_COPY copyfiles )
        
        # The intermediate target for copying
        add_custom_target(  copyfiles
                            COMMENT "Copying installer files to temporary location..."
                            DEPENDS ${PROJECT_NAME} )
                            
        add_dependencies( makeinstaller copyfiles )
    endif()
    
    if ( WIN32 OR APPLE )
        set( FC_CLI_NAME FlightCrew-cli )
    else()
        set( FC_CLI_NAME flightcrew-cli )
    endif()
    
    # We want to include the CLI in the installer, so it has to be built
    add_dependencies( makeinstaller ${FC_CLI_NAME} )
    
    # Copy MPI file to temp folder location
    add_custom_command( TARGET ${TARGET_FOR_COPY} PRE_BUILD 
                        COMMAND cmake -E copy ${CMAKE_SOURCE_DIR}/installer/FlightCrew.mpi ${MPI_LOCATION} )                        
    
    # Copy ISS file to temp folder location
    add_custom_command( TARGET ${TARGET_FOR_COPY} PRE_BUILD 
                        COMMAND cmake -E copy ${ISS_CONFIGURED_LOCATION} ${ISS_TEMP_LOCATION} )     

    # Copy Qt runtime libs
    set( QT_LIBS QtCore QtGui QtNetwork )
    
    if( UNIX )
        # DBus is needed on Linux
        list( APPEND QT_LIBS QtDBus )
    endif()

    add_custom_command( TARGET ${TARGET_FOR_COPY} PRE_BUILD COMMAND cmake -E make_directory ${MAIN_PACKAGE_DIR}/ )    
    foreach( lib ${QT_LIBS} )
        set( location location-NOTFOUND )
        find_file( location ${lib} NAMES ${lib}4.dll lib${lib}.so.4 PATHS ${QT_LIBRARY_DIR} )
        add_custom_command( TARGET ${TARGET_FOR_COPY} PRE_BUILD COMMAND cmake -E copy ${location} ${MAIN_PACKAGE_DIR}/ )
    endforeach( lib )
    
    # Set the path of the application executable
    if( MSVC_IDE )
        set( EXE_PATH     ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/${PROJECT_NAME}${CMAKE_EXECUTABLE_SUFFIX} )
        set( CLI_EXE_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/${FC_CLI_NAME}${CMAKE_EXECUTABLE_SUFFIX} )        
    else()
        set( EXE_PATH     ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}${CMAKE_EXECUTABLE_SUFFIX} )
        set( CLI_EXE_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${FC_CLI_NAME}${CMAKE_EXECUTABLE_SUFFIX} )   
    endif()

    # Copy the application executable
    add_custom_command( TARGET ${TARGET_FOR_COPY} PRE_BUILD 
                        COMMAND cmake -E copy ${EXE_PATH} ${MAIN_PACKAGE_DIR} )
                        
    # Copy the CLI application executable
    add_custom_command( TARGET ${TARGET_FOR_COPY} PRE_BUILD 
                        COMMAND cmake -E copy ${CLI_EXE_PATH} ${MAIN_PACKAGE_DIR} )
                        
    # We need to copy the CRT dlls
    if ( WIN32 )
        # Add -DWIN_INSTALLER_USE_64BIT_CRT=1 to the cmake call if you want to build
        # an installer for the x64 verison of Sigil. This will make sure that the
        # correct CRT libs are included in the installer.
        if ( WIN_INSTALLER_USE_64BIT_CRT )
            message( STATUS "Using the 64 bit CRT in the FlightCrew Windows installer" )
            add_custom_command( TARGET ${TARGET_FOR_COPY} PRE_BUILD 
                COMMAND cmake -E copy ${CMAKE_SOURCE_DIR}/installer/msvc_crt/x64/msvcp100.dll ${MAIN_PACKAGE_DIR} )
            add_custom_command( TARGET ${TARGET_FOR_COPY} PRE_BUILD 
                COMMAND cmake -E copy ${CMAKE_SOURCE_DIR}/installer/msvc_crt/x64/msvcr100.dll ${MAIN_PACKAGE_DIR} )
        else()
            message( STATUS "Using the 32 bit CRT in the FlightCrew Windows installer" )
            add_custom_command( TARGET ${TARGET_FOR_COPY} PRE_BUILD 
                COMMAND cmake -E copy ${CMAKE_SOURCE_DIR}/installer/msvc_crt/x86/msvcp100.dll ${MAIN_PACKAGE_DIR} )
            add_custom_command( TARGET ${TARGET_FOR_COPY} PRE_BUILD 
                COMMAND cmake -E copy ${CMAKE_SOURCE_DIR}/installer/msvc_crt/x86/msvcr100.dll ${MAIN_PACKAGE_DIR} )            
        endif()
    endif()

    if( UNIX )
        # Copy the Unix launcher that adds the working directory to the LD_LIBRARY_PATH
        add_custom_command( TARGET ${TARGET_FOR_COPY} PRE_BUILD 
                            COMMAND cmake -E copy ${PROJECT_SOURCE_DIR}/resources/bash/flightcrew-gui.sh ${MAIN_PACKAGE_DIR} )
    endif()
                        
    # Copy the Changelog
    add_custom_command( TARGET ${TARGET_FOR_COPY} PRE_BUILD 
                        COMMAND cmake -E copy ${CMAKE_SOURCE_DIR}/ChangeLog.txt ${MAIN_PACKAGE_DIR} )                     
    
    # Copy the license files
    add_custom_command( TARGET ${TARGET_FOR_COPY} PRE_BUILD 
                        COMMAND cmake -E copy ${CMAKE_SOURCE_DIR}/COPYING.txt ${MAIN_PACKAGE_DIR} )
    add_custom_command( TARGET ${TARGET_FOR_COPY} PRE_BUILD 
                        COMMAND cmake -E copy ${CMAKE_SOURCE_DIR}/COPYING.LESSER.txt ${MAIN_PACKAGE_DIR} )                          
                        
    # Remove the temp directory used for building the installer 
    add_custom_command( TARGET makeinstaller POST_BUILD 
                        COMMAND cmake -E remove_directory ${TEMP_PACKAGE_DIR}
                        COMMENT "Removing temporary directory..." )
endif()

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
