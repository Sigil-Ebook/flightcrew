
FlightCrew is a C++, cross-platform, native code epub validator.
The version of the package can be found in the ChangeLog.txt file.

It's website is located here: http://code.google.com/p/flightcrew/

The src directory contains all of the source code. It has
a few subdirectories:
    src/BoostParts - source code of various parts of the Boost C++ 
                     Libraries that FlightCrew uses;
    src/FlightCrew - source code for the FlightCrew, the validation 
                     library;
    src/FlightCrew-cli - the command-line front-end to the FlightCrew
                         library; 
    src/FlightCrew-gui - the GUI front-end to the FlightCrew library;
    src/googlemock - a framework used for the test suite
    src/utf8-cpp - a header-only library for dealing with utf-8 in C++
    src/Xerces - an XML parser
    src/XercesExtensions - a library containing some common wrapper 
                           code for Xerces; this lib is part of FC
    src/Zipios - a ZIP library
    src/zlib - a lib for data compression (the DEFLATE algorithm)
    
The entire public interface of the library can be accessed by including
the src/FlightCrew/flightcrew.h header file.

The installer directory contains the files needed to produce
a binary installer for Windows and Linux.

The INSTALL.txt file contains information on building FlightCrew 
from source code (and installing it on Linux machines).

The LGPLv3 license under which Sigil is released is located in
the file called COPYING.txt and COPYING.LESSER.txt.