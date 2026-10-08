import math


# ---------------------------------------------------------
# C Keywords
# ---------------------------------------------------------

keywords = {
    "auto", "break", "case", "char", "const",
    "continue", "default", "do", "double",
    "else", "enum", "extern", "float", "for",
    "goto", "if", "int", "long", "register",
    "return", "short", "signed", "sizeof",
    "static", "struct", "switch", "typedef",
    "union", "unsigned", "void", "volatile",
    "while"
}


# ---------------------------------------------------------
# Operators
# ---------------------------------------------------------

operators = {
    "+", "-", "*", "/", "%",
    "=", "+=", "-=", "*=", "/=", "%=",
    "==", "!=", "<", ">", "<=", ">=",
    "&&", "||", "!",
    "++", "--",
    "&", "|", "^", "~",
    "<<", ">>",
    "<<=", ">>=",
    "&=", "|=", "^=",
    "?", ":"
}


# ---------------------------------------------------------
# Delimiters
# ---------------------------------------------------------

delimiters = {
    ",", ";", "(", ")", "{", "}",
    "[", "]"
}


# ---------------------------------------------------------
# Read C Program
# ---------------------------------------------------------

filename = input("Enter C program file name: ")

try:

    with open(filename, "r") as file:
        code = file.read()

except FileNotFoundError:

    print("File not found.")
    exit()


# ---------------------------------------------------------
# Remove Comments
# ---------------------------------------------------------

code_without_comments = ""

i = 0

while i < len(code):

    # Single line comment
    if code[i:i + 2] == "//":

        while i < len(code) and code[i] != "\n":
            i += 1

    # Multi-line comment
    elif code[i:i + 2] == "/*":

        i += 2

        while i < len(code) - 1:

            if code[i:i + 2] == "*/":

                i += 2
                break

            i += 1

    else:

        code_without_comments += code[i]
        i += 1


# ---------------------------------------------------------
# Remove Preprocessor Lines
# ---------------------------------------------------------

lines = code_without_comments.splitlines()

code_without_comments = ""

for line in lines:

    line = line.strip()

    if line.startswith("#"):
        continue

    code_without_comments += line + "\n"


# ---------------------------------------------------------
# Tokenize Program
# ---------------------------------------------------------

all_operators = []
all_operands = []

i = 0
n = len(code_without_comments)

while i < n:

    ch = code_without_comments[i]


    # -----------------------------------------------------
    # Ignore White Space
    # -----------------------------------------------------

    if ch.isspace():

        i += 1
        continue


    # -----------------------------------------------------
    # Ignore String Constants
    # -----------------------------------------------------

    if ch == '"':

        i += 1

        while i < n:

            # Escape sequence such as \n, \t, \"
            if code_without_comments[i] == "\\":

                i += 2
                continue

            # End of string
            if code_without_comments[i] == '"':

                i += 1
                break

            i += 1

        continue


    # -----------------------------------------------------
    # Ignore Character Constants
    # -----------------------------------------------------

    if ch == "'":

        i += 1

        while i < n:

            if code_without_comments[i] == "\\":

                i += 2
                continue

            if code_without_comments[i] == "'":

                i += 1
                break

            i += 1

        continue


    # -----------------------------------------------------
    # Identifier / Keyword
    # -----------------------------------------------------

    if ch.isalpha() or ch == "_":

        start = i

        i += 1

        while i < n:

            if (
                code_without_comments[i].isalnum()
                or code_without_comments[i] == "_"
            ):

                i += 1

            else:

                break

        word = code_without_comments[start:i]


        # Keyword = Operator
        if word in keywords:

            all_operators.append(word)

        # Identifier = Operand
        else:

            all_operands.append(word)

        continue


    # -----------------------------------------------------
    # Numeric Constant = Operand
    # -----------------------------------------------------

# -----------------------------------------------------
# Ignore Numeric Constants
# -----------------------------------------------------

    if ch.isdigit():

        i += 1

        while i < n:

            if (
                code_without_comments[i].isdigit()
                or code_without_comments[i] == "."
            ):

                i += 1

            else:

                break

        continue


    # -----------------------------------------------------
    # Three Character Operator
    # -----------------------------------------------------

    op = code_without_comments[i:i + 3]

    if op in operators:

        all_operators.append(op)

        i += 3

        continue


    # -----------------------------------------------------
    # Two Character Operator
    # -----------------------------------------------------

    op = code_without_comments[i:i + 2]

    if op in operators:

        all_operators.append(op)

        i += 2

        continue


    # -----------------------------------------------------
    # One Character Operator
    # -----------------------------------------------------

    if ch in operators:

        all_operators.append(ch)

        i += 1

        continue


    # -----------------------------------------------------
    # Ignore Delimiters
    # -----------------------------------------------------

    if ch in delimiters:

        i += 1
        continue


    # -----------------------------------------------------
    # Ignore Unknown Character
    # -----------------------------------------------------

    i += 1


# ---------------------------------------------------------
# Unique Operators and Operands
# ---------------------------------------------------------

unique_operators = set(all_operators)

unique_operands = set(all_operands)


# ---------------------------------------------------------
# Total Operators and Operands
# ---------------------------------------------------------

N1 = len(all_operators)

N2 = len(all_operands)


# ---------------------------------------------------------
# Distinct Operators and Operands
# ---------------------------------------------------------

eta1 = len(unique_operators)

eta2 = len(unique_operands)


# ---------------------------------------------------------
# Actual Program Length
# ---------------------------------------------------------

N = N1 + N2


# ---------------------------------------------------------
# Expected Program Length
# ---------------------------------------------------------

Ne = 0

if eta1 > 0:

    Ne += eta1 * math.log2(eta1)

if eta2 > 0:

    Ne += eta2 * math.log2(eta2)


# ---------------------------------------------------------
# Program Volume
# ---------------------------------------------------------

if eta1 + eta2 > 0:

    V = N * math.log2(eta1 + eta2)

else:

    V = 0


# ---------------------------------------------------------
# Find Input Operands
# ---------------------------------------------------------

input_operands = set()

i = 0

while i < n:

    # Find scanf
    if code_without_comments[i:i + 5] == "scanf":

        i += 5

        # Find opening bracket
        while (
            i < n
            and code_without_comments[i] != "("
        ):

            i += 1

        i += 1

        # Search until closing bracket
        while (
            i < n
            and code_without_comments[i] != ")"
        ):

            # Address operator &
            if code_without_comments[i] == "&":

                i += 1

                # Ignore spaces
                while (
                    i < n
                    and code_without_comments[i].isspace()
                ):

                    i += 1

                start = i

                # Read identifier
                while (
                    i < n
                    and (
                        code_without_comments[i].isalnum()
                        or code_without_comments[i] == "_"
                    )
                ):

                    i += 1

                if i > start:

                    input_operands.add(
                        code_without_comments[start:i]
                    )

            else:

                i += 1

    else:

        i += 1


# ---------------------------------------------------------
# Distinct Input Operands
# ---------------------------------------------------------

eta2_star = len(input_operands)


# ---------------------------------------------------------
# Program Critical Volume
# ---------------------------------------------------------

Vc = (
    (2 + eta2_star)
    * math.log2(2 + eta2_star)
)


# ---------------------------------------------------------
# Program Level
# ---------------------------------------------------------

if V != 0:

    L = Vc / V

else:

    L = 0


# ---------------------------------------------------------
# Effort
# ---------------------------------------------------------

if L != 0:

    E = V / L

else:

    E = 0


# ---------------------------------------------------------
# Program Time
# ---------------------------------------------------------

mental_discrimination = 18

time_seconds = E * mental_discrimination

time_minutes = time_seconds / 60


# ---------------------------------------------------------
# Number of People
# ---------------------------------------------------------

# Development duration = 5 months
# Assuming 30 days in one month

development_time = 5 * 30 * 24 * 60

people = time_minutes / development_time


# ---------------------------------------------------------
# Menu
# ---------------------------------------------------------

while True:

    print("\n========================================")
    print("       STRUCTURAL COMPLEXITY")
    print("========================================")

    print("1. Unique Operators and Operands")
    print("2. Total Operators and Operands")
    print("3. Actual Program Length")
    print("4. Expected Program Length")
    print("5. Program Volume")
    print("6. Program Critical Volume")
    print("7. Program Level")
    print("8. Effort")
    print("9. Program Time")
    print("10. Number of People")
    print("11. Display All")
    print("0. Exit")

    choice = int(input("Enter your choice: "))


    # -----------------------------------------------------
    # Option 1
    # -----------------------------------------------------

    if choice == 1:

        print("\nUnique Operators:")
        print(unique_operators)

        print("\nUnique Operands:")
        print(unique_operands)

        print("\nInput Operands:")
        print(input_operands)


    # -----------------------------------------------------
    # Option 2
    # -----------------------------------------------------

    elif choice == 2:

        print("\nTotal Operators =", N1)
        print("Total Operands =", N2)


    # -----------------------------------------------------
    # Option 3
    # -----------------------------------------------------

    elif choice == 3:

        print("\nActual Program Length =", N)


    # -----------------------------------------------------
    # Option 4
    # -----------------------------------------------------

    elif choice == 4:

        print("\nExpected Program Length =", Ne)


    # -----------------------------------------------------
    # Option 5
    # -----------------------------------------------------

    elif choice == 5:

        print("\nProgram Volume =", V, "bits")


    # -----------------------------------------------------
    # Option 6
    # -----------------------------------------------------

    elif choice == 6:

        print("\nProgram Critical Volume =", Vc, "bits")


    # -----------------------------------------------------
    # Option 7
    # -----------------------------------------------------

    elif choice == 7:

        print("\nProgram Level =", L)


    # -----------------------------------------------------
    # Option 8
    # -----------------------------------------------------

    elif choice == 8:

        print("\nEffort =", E)


    # -----------------------------------------------------
    # Option 9
    # -----------------------------------------------------

    elif choice == 9:

        print("\nProgram Time =", time_seconds, "seconds")

        print(
            "Program Time =",
            time_minutes,
            "minutes"
        )


    # -----------------------------------------------------
    # Option 10
    # -----------------------------------------------------

    elif choice == 10:

        print("\nNumber of People =", people)


    # -----------------------------------------------------
    # Option 11
    # -----------------------------------------------------

    elif choice == 11:

        print("\n========================================")
        print("                 RESULT")
        print("========================================")

        print("\nUnique Operators =", eta1)
        print("Unique Operands =", eta2)

        print("\nTotal Operators =", N1)
        print("Total Operands =", N2)

        print("\nActual Program Length =", N)
        print("Expected Program Length =", Ne)

        print("\nProgram Volume =", V)
        print("Program Critical Volume =", Vc)

        print("\nProgram Level =", L)

        print("\nEffort =", E)

        print("\nProgram Time =", time_seconds, "seconds")
        print("Program Time =", time_minutes, "minutes")

        print("\nNumber of People =", people)


    # -----------------------------------------------------
    # Exit
    # -----------------------------------------------------

    elif choice == 0:

        print("\nProgram ended.")

        break


    # -----------------------------------------------------
    # Invalid Choice
    # -----------------------------------------------------

    else:

        print("\nInvalid choice.")