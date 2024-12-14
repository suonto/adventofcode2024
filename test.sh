#!/bin/bash

set -e
set -u

cmake -S . -B build && cmake --build build
cd build && ctest -- $@

