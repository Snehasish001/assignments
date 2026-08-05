#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Usage: ./count_lines.txt <filename>"
    exit 1
fi

if [ ! -f "$1" ]
then
    echo "File does not exist!"
    exit 1
fi

lines=$(wc -l < "$1")

echo "Number of lines in $1 = $lines"