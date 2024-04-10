#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
GREP_PATH="./s21_grep"
TEST_FILES="test1.txt" # test0.txt test2.txt"

echo "" > log.txt

for ip in "-e hello" "-e biba -e hello"
do
    for if1 in -i -v -c -l -n -h -o ""
    do
        for if2 in "" -i -v -c -l -n -h -o
        do
            TEST="$if1 $if2 $ip $TEST_FILES"
            echo "$TEST"

            $GREP_PATH $TEST > s21_grep.txt
            grep $TEST > grep.txt

            DIFF_RES=$(diff s21_grep.txt grep.txt)
            if [[ "$DIFF_RES" == "" ]]
            then
                (( COUNTER_SUCCESS++ ))
            else
                echo "$TEST" >> log.txt
                (( COUNTER_FAIL++ ))
            fi
        done
    done
done

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"

rm s21_grep.txt grep.txt
