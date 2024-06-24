#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Check if the input file and output file are provided
if [ -z "$1" ] || [ -z "$2" ]; then
    echo "Usage: $0 <input_file> <output_file>"
    exit 1
fi

INPUT_FILE=$1
OUTPUT_FILE=$2

# Determine file type and validate accordingly
if [[ "$INPUT_FILE" == *.xml ]]; then
    ./validate_xml.sh "$INPUT_FILE"
elif [[ "$INPUT_FILE" == *.json ]]; then
    ./validate_json.sh "$INPUT_FILE"
else
    echo "Unsupported file format. Please provide an XML or JSON file."
    exit 1
fi

# Build the project
./build.sh

# Run the C++ program with the input file and redirect output to the specified output file
./main "$INPUT_FILE" > "$OUTPUT_FILE"

echo "Program executed successfully. Output written to $OUTPUT_FILE"