#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Build the project
./build.sh

# Run the C++ program
./main

echo "Program executed successfully."