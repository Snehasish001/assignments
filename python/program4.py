import re

phone_re = r'^(\+91\s?)?[6-9]\d{4}\s?\d{5}$'

while True:
    phone = input("Enter phone number: ")

    if re.fullmatch(phone_re, phone):
        print("Valid")
    else:
        print("Invalid")