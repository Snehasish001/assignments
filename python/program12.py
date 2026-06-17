import string

# string.ascii_lowercase gives the string 'abcdefghijklmnopqrstuvwxyz'
lowercase_letters = string.ascii_lowercase

# Enumerate starting from 1
enumerated_letters = list(enumerate(lowercase_letters, start=1))

print(enumerated_letters)
