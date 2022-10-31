#!/bin/bash

mkdir -p build_device
cmake -B build_device -DTARGET_GROUP=device -DLOG_LEVEL=3 .
make -C build_device --no-print-directory