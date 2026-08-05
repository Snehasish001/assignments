#!/bin/bash

echo "Enter a 4-digit number:"
read num

if [[ ! $num =~ ^[0-9]{4}$ ]]
then
    echo "Error: Please enter a valid 4-digit number."
    exit
fi

d1=$((num / 1000))
d2=$(((num / 100) % 10))
d3=$(((num / 10) % 10))
d4=$((num % 10))

sum=$((d1 + d2 + d3 + d4))

echo "Sum of digits = $sum"
echo "Reverse = $d4$d3$d2$d1"