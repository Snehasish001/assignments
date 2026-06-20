
class UserError(Exception):
    pass


class UsernameNotUniqueError(UserError):
    pass


class InvalidAgeError(UserError):
    pass


class UnderAgeError(UserError):
    pass


class InvalidEmailError(UserError):
    pass


users = [
    ("rahul", "rahul@gmail.com", 20),
    ("amit", "amit@yahoo.com", 17),
    ("rahul", "rahul2@gmail.com", 25),
    ("sita", "sita.gmail.com", 22),
    ("gita", "gita@gmail.com", -5),
    ("rani", "rani@gmail.com", 15),
    ("soham", "soham@gmail.com", 18)
]


directory = {}
usernames = set()


for username, email, age in users:

    try:

        if username in usernames:
            raise UsernameNotUniqueError(
                f"Username '{username}' already exists."
            )

        if not isinstance(age, int) or age <= 0:
            raise InvalidAgeError(
                f"Invalid age '{age}'. Age must be positive."
            )


        if age < 16:
            raise UnderAgeError(
                f"User '{username}' is under 16."
            )


        if "@" not in email or "." not in email.split("@")[-1]:
            raise InvalidEmailError(
                f"Invalid email '{email}'."
            )


        directory[username] = {
            "email": email,
            "age": age
        }

        usernames.add(username)

        print(f"{username} added successfully.")

    except UsernameNotUniqueError as e:
        print("Username Error :", e)

    except InvalidAgeError as e:
        print("Age Error      :", e)

    except UnderAgeError as e:
        print("Under Age Error:", e)

    except InvalidEmailError as e:
        print("Email Error    :", e)


print("\nValid Users Directory")
print(directory)