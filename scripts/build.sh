#!/bin/sh

TARGET=${1:-release}

# rm -rf build #comment out if not needed
mkdir -p build
cmake -B build -DTARGET_GROUP=$TARGET .
make -C build --no-print-directory