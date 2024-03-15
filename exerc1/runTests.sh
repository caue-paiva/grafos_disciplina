#!/bin/bash

# compile the program
make

# counters for passed and failed tests
passed=0
failed=0

# array to store names of failed test files
declare -a failed_tests

# Change the directory if your test files are located in a different directory
cd test

# find all input files and iterate over them
for input_file in *.in; do
    # Extract the test number from the file name
    test_number=$(echo $input_file | sed 's/\([0-9]*\)\.in/\1/')

    # Construct the name of the corresponding output file
    output_file="$test_number.out"
    if [ ! -f $output_file ]; then
        echo "Output file for test $test_number not found."
        continue
    fi

    # Run the program with the input file and save the output to a temporary file
    # 10-second timeout using 'timeout' command
    start_time=$(date +%s)
    if timeout 10s ./main < $input_file > temp_out.txt; then
        end_time=$(date +%s)
        elapsed_time=$(( end_time - start_time ))

        if [ $elapsed_time -ge 10 ]; then
            echo "Test $test_number failed (timeout)"
            ((failed++))
            failed_tests+=($test_number)
        else
            # Compare the program's output with the expected output
            if diff -w -B -Z temp_out.txt $output_file > /dev/null; then
                echo "Test $test_number passed"
                ((passed++))
            else
                echo "Test $test_number failed"
                ((failed++))
                failed_tests+=($test_number)
                echo "Failed Test $test_number:"
                echo "Output Produced:"
                cat temp_out.txt
                echo "Expected Output:"
                cat $output_file
                echo "-------------------------"
            fi
        fi
    else
        # If the program did not finish before the timeout or if 'timeout' command fails
        echo "Test $test_number failed (timeout error)"
        ((failed++))
        failed_tests+=($test_number)
    fi
done

# Change back to the original directory if needed
cd -

# Remove the temporary output file
rm test/temp_out.txt

# Display the number of passed and failed tests
echo "$passed tests passed"
echo "$failed tests failed"

# List the names of the tests that failed
if [ $failed -ne 0 ]; then
    echo "Failed test numbers:"
    for number in "${failed_tests[@]}"; do
        echo $number
    done
fi
