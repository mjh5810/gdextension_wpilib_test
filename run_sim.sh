#!/bin/sh

pushd allwpilib/build-cmake
HALSIM_EXTENSIONS="./lib/libhalsim_gui.so:./lib/libhalsim_xrp.so" HALSIMXRP_HOST="192.168.42.1" ./bin/developerRobotCpp
popd
