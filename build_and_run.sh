#!/bin/bash

# Exit immediately if any command fails
set -e

echo "Configuring the project with CMake..."
cmake -B build

echo "Compiling..."
cmake --build build

# Clear the screen before running the app
clear

# Check common output paths for Mac/Linux
if [ -f "build/StableMarriageApp" ]; then
    ./build/StableMarriageApp
else
    echo "[ERROR] Could not find executable at build/StableMarriageApp"
fi
