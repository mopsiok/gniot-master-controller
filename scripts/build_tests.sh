#!/bin/bash

mkdir -p build_tests
cmake -B build_tests -DTARGET_GROUP=test -DLOG_LEVEL=3 .
make -C build_tests --no-print-directory