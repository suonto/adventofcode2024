#!/bin/bash

set -e
set -u

print_usage() {
    echo "Usage: $0 <day> <variant>"
    echo "Day number arg1 must be exactly 2 digits and variant A or B."
}

# Check if the number of arguments is 2
if [ "$#" -ne 2 ]; then
    print_usage
    exit 1
fi

if ! [[ "$1" =~ ^[0-9]{2}$ ]] || [[ "$2" != "A" ]] && [[ "$2" != "B" ]]; then
    print_usage
    exit 1
fi

cmake -S . -B build && cmake --build build
./build/main_${1} $2
