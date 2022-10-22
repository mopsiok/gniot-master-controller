#!/bin/sh

# rm -rf build #comment out if not needed
mkdir -p build
cmake -B build -DTARGET_GROUP=$1 .
make -C build --no-print-directory