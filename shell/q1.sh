# Write a shell script that asks for the values of 2 variables: userv1 and userv2, from the
# user and takes in any type (real/integer/character). Try to perform the following
# operations on the variables: (a) add, (b) multiply (c) subtract (d) division. Print
# appropriate error message/s if the operation cannot be performed, otherwise print the
# result: “the sum of ‘userv1’ and ‘userv2’ is ….”. Execute the shell script as many number
# of times the user wants. Show all possible combinations of the types of variables and
# result/s of the corresponding operation/s.


real_re='^-?[0-9]+(\.[0-9]+)?$'

while true
do
    read -p "Enter userv1: " userv1
    read -p "Enter userv2: " userv2

    if [[ $userv1 =~ $real_re ]] && [[ $userv2 =~ $real_re ]]
    then
        echo "Results:"

        add=$(echo "$userv1 + $userv2" | bc)
        sub=$(echo "$userv1 - $userv2" | bc)
        mul=$(echo "$userv1 * $userv2" | bc)
        div=$(echo "scale=2; $userv1 / $userv2" | bc)

        echo "The sum of '$userv1' and '$userv2' is $add"
        echo "The difference of '$userv1' and '$userv2' is $sub"
        echo "The product of '$userv1' and '$userv2' is $mul"

        if [[ $userv2 == 0 || $userv2 == 0.0 ]]
        then
            echo "Division cannot be performed (division by zero)"
        else
            echo "The division of '$userv1' and '$userv2' is $div"
        fi

    else
        echo "Arithmetic operations cannot be performed."
        echo "Both values must be numeric (integer or real)."
    fi

    read -p "Continue (y/n)? " ch
    [[ $ch != [Yy] ]] && break
done