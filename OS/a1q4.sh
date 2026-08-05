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

echo
echo "===== Files ====="
find "$dir" -maxdepth 1 -type f -printf "%f\n"
fileCount=$(find "$dir" -maxdepth 1 -type f | wc -l)
echo "Total Files: $fileCount"

echo
echo "===== Directories ====="
find "$dir" -maxdepth 1 -type d -printf "%f\n"
dirCount=$(find "$dir" -maxdepth 1 -type d | wc -l)
echo "Total Directories: $dirCount"

echo
echo "Total Files + Directories: $((fileCount + dirCount))"

echo
echo "Total size of files created/modified in the last 7 days:"
find "$dir" -maxdepth 1 -type f -mtime -7 -printf "%s\n" | \
awk '{sum += $1} END {print sum, "bytes"}'