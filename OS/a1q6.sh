#!/bin/bash

echo "Directories in PATH:"
echo "------------------------------"

echo $PATH | tr ":" "\n" | while read dir
do
    echo
    echo "Directory: $dir"

    if [ -d "$dir" ]
    then
        ls -ld "$dir"
    else
        echo "Directory does not exist."
    fi
done