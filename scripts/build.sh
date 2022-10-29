#!/bin/bash

LAST_TARGET_FILE_PATH=scripts/last_target.log

TARGET=${1:-device}

# get last build target
if ! [ -f $LAST_TARGET_FILE_PATH ]; then
    LAST_TARGET=notfound
else
    LAST_TARGET=`cat $LAST_TARGET_FILE_PATH`
fi

# remove build directory if needed
echo "Chosen target: $TARGET"
echo "Last build was for target: $LAST_TARGET"
if [ $TARGET != $LAST_TARGET ]; then
    echo "Toolchain change, rebuild needed."
    rm -rf build
else
    echo "Using previous configuration."
fi

# build target
mkdir -p build
cmake -B build -DTARGET_GROUP=$TARGET .
make -C build --no-print-directory

# update target file
echo $TARGET > $LAST_TARGET_FILE_PATH