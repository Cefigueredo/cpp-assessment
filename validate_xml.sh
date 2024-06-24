#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Check if the input file is provided
if [ -z "$1" ]; then
    echo "Usage: $0 <xml_file>"
    exit 1
fi

XML_FILE=$1

# Validate the XML file
if xmllint --noout "$XML_FILE"; then
    echo "XML file is valid."
else
    echo "XML file is invalid."
    exit 1
fi
