#!/bin/bash

echo "Enter directory path (Press Enter for current directory):"
read dir

if [ -z "$dir" ]
then
    dir="."
fi

if [ ! -d "$dir" ]
then
    echo "Directory does not exist!"
    exit
fi

# (a) Total size of all files
total=$(find "$dir" -maxdepth 1 -type f -printf "%s\n" | \
awk '{sum += $1} END {print sum}')

echo "Total bytes used by all files: $total bytes"

# (b) Total size of today's files (modified today)
today=$(find "$dir" -maxdepth 1 -type f -daystart -mtime 0 -printf "%s\n" | \
awk '{sum += $1} END {print sum}')

echo "Total size of files modified today: $today bytes"