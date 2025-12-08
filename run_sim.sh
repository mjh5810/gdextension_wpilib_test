#!/bin/sh

pushd allwpilib/build-cmake
HALSIM_EXTENSIONS="./lib/libhalsim_gui.so:./lib/libhalsim_xrp.so" HALSIMXRP_HOST="localhost" ./bin/developerRobotCpp
popd
