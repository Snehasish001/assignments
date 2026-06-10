# ================= REGEX BASICS IN BASH =================
#
# Syntax:
# [[ string =~ regex ]]
#
# =~  : Checks whether the string matches the regex pattern.
#
# Example:
#
# if [[ $1 =~ hello ]]
# then
#     echo "Matched"
# fi
#
# ---------------------------------------------------------

# 1. Literal Text
#
# hello
#
# Matches:
# hello
# hello123
# abchello
#
# Example:
# [[ "hello world" =~ hello ]]

# ---------------------------------------------------------

# 2. ^ (Start of String)
#
# ^hello
#
# Matches:
# hello
# hello123
#
# Does NOT Match:
# xhello

# Example:
# [[ "hello123" =~ ^hello ]]

# ---------------------------------------------------------

# 3. $ (End of String)
#
# hello$
#
# Matches:
# hello
# abchello
#
# Does NOT Match:
# hello123

# Example:
# [[ "abchello" =~ hello$ ]]

# ---------------------------------------------------------

# 4. Exact Match
#
# ^hello$
#
# Matches:
# hello
#
# Does NOT Match:
# hello123
# abchello

# Example:
# [[ "hello" =~ ^hello$ ]]

# ---------------------------------------------------------

# 5. Character Classes []

# [0-9]
# Any one digit

# Matches:
# 0
# 5
# 9

# Example:
# [[ "5" =~ [0-9] ]]

# ---------------------------------------------------------

# [a-z]
# Any lowercase letter

# Matches:
# a
# m
# z

# ---------------------------------------------------------

# [A-Z]
# Any uppercase letter

# Matches:
# A
# M
# Z

# ---------------------------------------------------------

# [a-zA-Z]
# Any alphabet

# Matches:
# A
# b
# Z

# ---------------------------------------------------------

# [a-zA-Z0-9]
# Any alphanumeric character

# Matches:
# A
# 5
# x

# ---------------------------------------------------------

# [^0-9]
# NOT a digit

# Matches:
# a
# @
#
# Does NOT Match:
# 5

# ---------------------------------------------------------

# 6. + (One or More)

# [0-9]+
#
# Matches:
# 1
# 123
# 99999
#
# Does NOT Match:
# (empty)

# Example:
# [[ "123" =~ ^[0-9]+$ ]]

# ---------------------------------------------------------

# 7. * (Zero or More)

# [0-9]*
#
# Matches:
# ""
# 1
# 123

# Example:
# [[ "" =~ ^[0-9]*$ ]]

# ---------------------------------------------------------

# 8. ? (Zero or One)

# colou?r
#
# Matches:
# color
# colour

# ---------------------------------------------------------

# 9. . (Any Single Character)

# h.llo
#
# Matches:
# hello
# hallo
# hxllo

# ---------------------------------------------------------

# 10. \ (Escape Character)

# . means any character
#
# To match actual dot:
#
# \.
#
# Example:
# 12\.34

# Matches:
# 12.34

# Does NOT Match:
# 12a34

# ---------------------------------------------------------

# 11. Grouping ()

#
# (abc)+
#
# Matches:
# abc
# abcabc
# abcabcabc

# ---------------------------------------------------------

# 12. Integer Regex

# ^[0-9]+$
#
# Matches:
# 10
# 123
#
# Does NOT Match:
# 12a
# abc

# ---------------------------------------------------------

# 13. Signed Integer Regex

# ^-?[0-9]+$
#
# Matches:
# 10
# -10
# 0

# ---------------------------------------------------------

# 14. Real Number Regex

# ^-?[0-9]+(\.[0-9]+)?$
#
# Matches:
# 10
# -10
# 2.5
# -3.14
#
# Does NOT Match:
# abc
# 1.2.3

# ---------------------------------------------------------

# 15. Alphabet Only

# ^[a-zA-Z]+$
#
# Matches:
# hello
# ABC
#
# Does NOT Match:
# hello123

# ---------------------------------------------------------

# 16. Email (Simple)

# ^[a-zA-Z0-9]+@[a-zA-Z0-9]+\.[a-zA-Z]+$
#
# Matches:
# abc@gmail.com
#
# Does NOT Match:
# abc@
# @gmail.com

# ---------------------------------------------------------

# 17. OR Operator

# cat|dog
#
# Matches:
# cat
# dog

# Example:
# [[ "dog" =~ cat|dog ]]

# ---------------------------------------------------------

# Common Bash Exam Regexes:
#
# ^[0-9]+$                  Integer
# ^-?[0-9]+$                Signed Integer
# ^-?[0-9]+(\.[0-9]+)?$     Integer or Real
# ^[a-zA-Z]+$               Alphabets Only
# ^[a-zA-Z0-9]+$            Alphanumeric
#
# Most Important Symbols:
#
# =~   regex match
# ^    start
# $    end
# []   character class
# [^]  negation
# +    one or more
# *    zero or more
# ?    optional
# .    any character
# \    escape special character
# ()   grouping
# |    OR


int_re='^-?(0|[1-9][0-9]*)$'

if [[ $1 =~ $int_re ]] 
then
    echo "$1"
else 
    echo "$1 not int"
fi