#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Define the source files and the output executable
SRC_FILES="*.cpp"
OUTPUT="main"

# Define the compiler and the compiler flags
CXX=g++
CXXFLAGS="-std=c++20 -Wall -Wextra"

# Build the project
echo "Compiling..."
$CXX $CXXFLAGS $SRC_FILES -o $OUTPUT

echo "Build successful. Executable is $OUTPUT"