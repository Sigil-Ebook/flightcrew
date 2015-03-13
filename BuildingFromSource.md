# General notes #

You will need CMake 2.8.0 or later on all platforms. You can download it [here](http://www.cmake.org/cmake/resources/software.html).

CMake is a cross-platform system for build automation. It can
generate Visual Studio project files on Windows, Xcode project files
on Mac OS X and Makefiles on Unix systems. After installing CMake,
you can see a list of generators provided on your system by typing
`cmake` in your terminal and pressing enter. The supported generators
should be listed near the bottom of the printout.

To build FlightCrew-gui, Qt 4.6.x is also required on all platforms. It can be downloaded [here](http://qt.nokia.com/downloads) (choose the LGPL version). **Qt is not necessary for the core FlightCrew library and FlightCrew-cli.**

Mac users should grab the Qt SDK. Windows users can also download the
SDK which comes with MinGW and the Qt Creator IDE. If you want to use
the Visual Studio compiler, you should download the precompiled Qt libraries for Visual Studio 2008 from Nokia's website. Linux users should get it from
their distribution's package manager (more information in the Linux
section).

On some platforms a `makeinstaller` target is provided for FlightCrew-gui which will build
a binary installer. For that to work, you need to have InstallJammer
installed and on the system PATH. You can get InstallJammer [here](http://www.installjammer.com/). You need to have the Qt libraries on the system PATH as well.

## Running the test suite ##

FlightCrew comes with an extensive test suite that should cover _all_ of the checks it performs, minus the ones coming from schemas. The default build procedure will build the `fc_tests` application that runs the tests. **You have to run `fc_tests` from the "bin" folder.** The application expects a `test_data` folder in the current working directory, so running it from any other directory will usually fail.

Note that I said that `test_data` is expected in "the current working directory", **not** the directory in which `fc_tests` is located. The two can be the same, but they can also be different.

## Compiling on Windows ##

It is assumed you want to generate Visual Studio project files. You can
do this by creating a new folder **outside** of the source distribution.

Now navigate to that folder with a terminal like cmd.exe or PowerShell.
Then type in and run the following:
```
cmake -G "Visual Studio 9 2008" /path/to/extracted/folder
```
This should create SLN and vcproj files for Visual Studio in that directory.
You can also generate project files for some other VS version. You can get
a list of all supported generators by typing in and running `cmake`.

The default build procedure will build `FlightCrew-gui.exe` and `FlightCrew-cli.exe`; if you want to package that with the required DLL's into an installer, build the `makeinstaller`
project.

There is also an [add-in](http://www.qtsoftware.com/downloads/visual-studio-add-in) for VS on Qt's website. It will make it easier to develop Qt applications like FlightCrew-gui, but is not
strictly necessary.

**NOTE:** If you generate solution files for VS 2010 with CMake version <= 2.8.1, those builds will fail. This is caused by [a bug](http://www.cmake.org/Bug/view.php?id=10503) in CMake. This bug has been fixed and CMake 2.8.2 and above don't have this problem.

## Compiling on Mac ##

It is assumed you want to generate Xcode project files. You can
do this by creating a new folder **outside** of the source distribution.

Now navigate to that folder with the Terminal. Then type in and run
the following:
```
cmake -G Xcode /path/to/extracted/folder
```
This should create Xcode project files in that directory. The default build procedure will build `FlightCrew-gui.app` and `FlightCrew-cli`; if you want to package `FlightCrew-gui.app` into a DMG file, invoke the `makedmg` build target.

## Compiling on Linux ##

If you want to build FlightCrew-gui you will need the core Qt libraries and **libqt4-dev**.

This should be as simple as typing in the following command into your
terminal (on Debian-like systems):
```
sudo apt-get install libqt4-gui libqt4-dev
```
It is assumed you want to generate Makefiles. You can do this by creating
a new folder **outside** of the source distribution.

Now navigate to that folder with a terminal. Then type in and run
the following:
```
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release /path/to/extracted/folder
make
sudo make install
```
That builds and installs FlightCrew-cli and FlightCrew-gui on Linux. By default, they are installed
in `${CMAKE_INSTALL_PREFIX}/bin`, with `CMAKE_INSTALL_PREFIX` defaulting to
`usr/local`.

You can change the install location by running cmake like this:
```
cmake -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX=/new/install/prefix -DCMAKE_BUILD_TYPE=Release /path/to/extracted/folder
```
Aside from using the install target, you can also build a binary
installer by invoking the `makeinstaller` build target.

Building from source in the repository is recommended, since code in the
repository should always be stable. If it's not, that's a bug report.

## Building FlightCrew as a DLL ##

**By default, FlightCrew is configured to build as a static library.** To compile it as a DLL, you need to do two things:
  * Pass "-DBUILD\_SHARED\_FC=1" (without the quotes) to the cmake call. So for Visual Studio 2008, it would look something like this:
```
cmake -G "Visual Studio 9 2008" -DBUILD_SHARED_FC=1 /path/to/extracted/folder
```
  * Define `FC_BUILT_AS_DLL` when including `flightcrew.h`

## Not building FlightCrew-gui ##

Just pass `-DSKIP_FC_GUI=1` to the cmake call. This can be passed along
with the option to build FlightCrew as a DLL.

## Not building the test executable ##

The default build procedure will also build a `fc_test` executable in the
`bin` directory of your build folder. Running this program runs the
FlightCrew test suite.

You can disable the building of this application by passing
`-DNO_TEST_EXE=1` to the cmake call. This can also be combined with the
other build options.

It is **highly** recommended to build and run the test application on your
system.

# Compiling Qt #

Compiling Qt directly should not be necessary. Nevertheless, if you wish to compile Qt, you should configure it before compiling like this:
```
configure -opensource -qt-zlib -qt-gif -qt-libpng -qt-libmng -qt-libtiff -qt-libjpeg
```
These are the options used to configure the Qt libraries that are provided with FlightCrew-gui on Windows.

Building Qt takes many hours. You can save yourself a lot of time by passing `-nomake tools -nomake examples -nomake demos -nomake docs -nomake translations` to `configure` as well. For Visual Studio builds, passing `-ltcg` is also strongly recommended.