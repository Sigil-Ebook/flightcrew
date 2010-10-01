#!/bin/sh

# Entry point for FlightCrew-gui on Unix systems.
# Adds the directory the FlightCrew-gui executable is located
# in to the LD_LIBRARY_PATH so the custom Qt libs
# are recognized and loaded.

appname=`basename $0 | sed s,\.sh$,,`

dirname=`dirname $0`
tmp="${dirname#?}"

if [ "${dirname%$tmp}" != "/" ]; then
dirname=$PWD/$dirname
fi
LD_LIBRARY_PATH=$dirname
export LD_LIBRARY_PATH
#if no agruments are passed then call just FlightCrew-gui program; else pass arguments.
if [$* == ""]
then
$dirname/$appname 
else
#argument may not be pass correctly without qoutation marks.
$dirname/$appname "$*"
fi
