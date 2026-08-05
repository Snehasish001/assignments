#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Usage: ./multiplication_table.sh <number>"
    exit 1
fi

num=$1

echo "Multiplication Table of $num"

for i in {1..10}
do
    echo "$num x $i = $((num * i))"
done