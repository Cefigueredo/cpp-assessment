#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Check if the input file is provided
if [ -z "$1" ]; then
    echo "Usage: $0 <json_file>"
    exit 1
fi

JSON_FILE=$1

# Validate the JSON file
if jq empty "$JSON_FILE"; then
    echo "JSON file is valid."
else
    echo "JSON file is invalid."
    exit 1
fi