#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Define test cases (pairs of input XML file and expected output file)
TEST_CASES=(
    "data/employees.xml output_test/expected_output1.txt"
    "data/employees.json output_test/expected_output2.txt"
    "data/employees_error.json output_test/expected_output3.txt"
    # Add more test cases as needed
)

# Build the project
./build.sh

# Run tests
for test_case in "${TEST_CASES[@]}"; do
    IFS=" " read -r xml_file expected_output <<< "$test_case"

    # Run the program and capture the output
    ./main "$xml_file" > output.txt

    # Compare the actual output with the expected output
    if diff -q output.txt "$expected_output"; then
        echo "Test with $xml_file passed."
    else
        echo "Test with $xml_file failed."
        exit 1
    fi
done

echo "All tests passed."
