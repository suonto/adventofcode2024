#!/bin/bash

set -e
set -u

print_usage() {
    echo "Usage: $0 <arg1> <arg2>"
    echo "Both arguments must be exactly 2 digits."
}

# Check if the number of arguments is 2
if [ "$#" -ne 2 ]; then
    print_usage
    exit 1
fi

# Check if both arguments are exactly 2 digits
if ! [[ "$1" =~ ^[0-9]{2}$ ]] || ! [[ "$2" =~ ^[0-9]{2}$ ]]; then
    print_usage
    exit 1
fi

arg1=$1
arg2=$2

# Function to copy directory if it does not exist
copy_if_not_exists() {
    src_dir=$1
    dest_dir=$2
    if [ ! -d "$dest_dir" ]; then
        cp -r $src_dir $dest_dir
        echo "Copied $src_dir to $dest_dir"
    else
        echo "Directory $dest_dir already exists, skipping copy."
    fi
}

# Copy directories recursively if they do not exist
copy_if_not_exists "src/$arg1/" "src/$arg2"
copy_if_not_exists "include/$arg1/" "include/$arg2"
copy_if_not_exists "tests/$arg1/" "tests/$arg2"

# Perform sed replacements
find "src/$arg2" -type f -exec sed -i "s/${arg1}\//${arg2}\//g" {} +
find "src/$arg2" -type f -exec sed -i "s/${arg1}_/${arg2}_/g" {} +
find "include/$arg2" -type f -exec sed -i "s/${arg1}\//${arg2}\//g" {} +
find "include/$arg2" -type f -exec sed -i "s/${arg1}_/${arg2}_/g" {} +
find "tests/$arg2" -type f -exec sed -i "s/${arg1}\//${arg2}\//g" {} +
find "tests/$arg2" -type f -exec sed -i "s/${arg1}_/${arg2}_/g" {} +
find "tests/$arg2" -type f -exec sed -i "s/Day${arg1}/Day${arg2}/g" {} +

echo "Reminder: Don't forget to edit CMakeLists.txt to include the new directories."
