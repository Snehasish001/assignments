#!/bin/bash

while true
do
    echo "Enter first value:"
    read userv1

    echo "Enter second value:"
    read userv2

    # Check if both are integers or real numbers
    if [[ $userv1 =~ ^-?[0-9]+([.][0-9]+)?$ && $userv2 =~ ^-?[0-9]+([.][0-9]+)?$ ]]
    then
        sum=$(echo "$userv1 + $userv2" | bc)
        sub=$(echo "$userv1 - $userv2" | bc)
        mul=$(echo "$userv1 * $userv2" | bc)

        if [ "$(echo "$userv2 == 0" | bc)" -eq 1 ]
        then
            div="Undefined (Division by Zero)"
        else
            div=$(echo "scale=2; $userv1 / $userv2" | bc)
        fi

        echo "Sum        = $sum"
        echo "Difference = $sub"
        echo "Product    = $mul"
        echo "Division   = $div"

    else
        echo "Error: Arithmetic operations cannot be performed on non-numeric values."
    fi

    echo
    echo "Do you want to continue? (y/n)"
    read ch

    if [ "$ch" != "y" ]
    then
        break
    fi
done