#!/bin/bash

cmake --version
cd /build
cmake -DCMAKE_BUILD_TYPE=RELEASE -DSKIP_FC_GUI=1 -DNO_TEST_EXE=1 /sources
make -j4
