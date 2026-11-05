import re
import math

# C/C++ keywords
KEYWORDS = {
    "auto", "break", "case", "char", "const", "continue",
    "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "int", "long", "register",
    "return", "short", "signed", "sizeof", "static", "struct",
    "switch", "typedef", "union", "unsigned", "void", "volatile",
    "while", "class", "public", "private", "protected", "virtual",
    "new", "delete", "this", "namespace", "using", "bool",
    "true", "false", "nullptr", "template", "typename", "try",
    "catch", "throw", "inline", "friend", "operator"
}

# Delimiters (excluded from Halstead calculations)
DELIMITERS = {",", ";", "(", ")"}

# Operators (longest operators are checked first)
OPERATORS = [
    "<<=", ">>=", "++", "--", "->", "==", "!=", "<=", ">=",
    "&&", "||", "+=", "-=", "*=", "/=", "%=", "&=", "|=",
    "^=", "<<", ">>", "::", ".*", "->*",
    "+", "-", "*", "/", "%", "=", "<", ">", "!",
    "&", "|", "^", "~", "?", ":", ".", "#",
    "{", "}", "[", "]"
]

# Valid numeric constants
NUMBER_PATTERN = re.compile(
    r"(?:"
    r"0[xX][0-9a-fA-F]+[uUlL]*"
    r"|0[bB][01]+[uUlL]*"
    r"|(?:\d+\.\d*|\.\d+|\d+)(?:[eE][+-]?\d+)?[fFlLuU]*"
    r")"
)


def transition_diagram(code):

    tokens = []
    invalid_identifiers = []
    invalid_constants = []
    invalid_operators = []

    i = 0
    n = len(code)

    while i < n:

        ch = code[i]

        # STATE 0: Whitespace
        if ch.isspace():
            i += 1
            continue

        # STATE 1: Single-line comment
        if code.startswith("//", i):
            while i < n and code[i] != "\n":
                i += 1
            continue

        # STATE 2: Multi-line comment
        if code.startswith("/*", i):
            end = code.find("*/", i + 2)

            if end == -1:
                print("Error: Unterminated comment")
                return tokens, invalid_identifiers, invalid_constants, invalid_operators

            i = end + 2
            continue

        # STATE 3: Preprocessor directive
        if ch == "#":

            j = i + 1

            while j < n and (code[j].isalnum() or code[j] == "_"):
                j += 1

            directive = code[i:j]

            tokens.append(("OPERATOR", directive))
            i = j

            # Handle #include <stdio.h>
            if directive == "#include":

                while i < n and code[i].isspace():
                    i += 1

                if i < n and code[i] == "<":

                    end = code.find(">", i + 1)

                    if end != -1:
                        tokens.append(("OPERATOR", "<"))
                        tokens.append(("OPERAND", code[i + 1:end]))
                        tokens.append(("OPERATOR", ">"))
                        i = end + 1
                    else:
                        invalid_identifiers.append(code[i:])
                        break

                elif i < n and code[i] == '"':

                    end = code.find('"', i + 1)

                    if end != -1:
                        tokens.append(("OPERAND", code[i + 1:end]))
                        i = end + 1
                    else:
                        invalid_identifiers.append(code[i:])
                        break

            continue

        # STATE 4: String constant
        if ch == '"':

            j = i + 1

            while j < n:

                if code[j] == "\\":
                    j += 2
                    continue

                if code[j] == '"':
                    break

                j += 1

            if j < n and code[j] == '"':
                tokens.append(("OPERAND", code[i:j + 1]))
                i = j + 1
            else:
                invalid_constants.append(code[i:j])
                i = j

            continue

        # STATE 5: Character constant
        if ch == "'":

            j = i + 1

            while j < n:

                if code[j] == "\\":
                    j += 2
                    continue

                if code[j] == "'":
                    break

                j += 1

            if j < n and code[j] == "'":
                tokens.append(("OPERAND", code[i:j + 1]))
                i = j + 1
            else:
                invalid_constants.append(code[i:j])
                i = j

            continue

        # STATE 6: Identifier / Keyword
        if ch.isalpha() or ch == "_":

            j = i + 1

            while j < n and (
                code[j].isalnum() or code[j] == "_"
            ):
                j += 1

            word = code[i:j]

            if word in KEYWORDS:
                tokens.append(("OPERATOR", word))

            else:

                # Check whether it is a function name
                k = j

                while k < n and code[k].isspace():
                    k += 1

                if k < n and code[k] == "(":
                    tokens.append(("OPERATOR", word))
                else:
                    tokens.append(("OPERAND", word))

            i = j
            continue

        # STATE 7: Numeric constant
        if ch.isdigit() or (
            ch == "." and i + 1 < n and code[i + 1].isdigit()
        ):

            j = i

            while j < n and (
                code[j].isalnum() or code[j] in "._"
            ):
                j += 1

            number = code[i:j]

            if NUMBER_PATTERN.fullmatch(number):
                tokens.append(("OPERAND", number))
            else:
                invalid_constants.append(number)

            i = j
            continue

        # STATE 8: Operator
        matched = False

        for op in OPERATORS:

            if code.startswith(op, i):

                tokens.append(("OPERATOR", op))
                i += len(op)
                matched = True
                break

        if matched:
            continue

        # STATE 9: Delimiter
        if ch in DELIMITERS:

            tokens.append(("DELIMITER", ch))
            i += 1
            continue

        # STATE 10: Invalid symbol
        invalid_operators.append(ch)
        i += 1

    return (
        tokens,
        invalid_identifiers,
        invalid_constants,
        invalid_operators
    )


# Find actual input operands from scanf()
def find_input_operands(tokens):

    input_operands = set()

    for i, token in enumerate(tokens):

        if token == ("OPERATOR", "scanf"):

            j = i + 1

            while j < len(tokens) and tokens[j] != ("DELIMITER", ")"):

                if (
                    tokens[j] == ("OPERATOR", "&")
                    and j + 1 < len(tokens)
                    and tokens[j + 1][0] == "OPERAND"
                ):

                    input_operands.add(tokens[j + 1][1])

                j += 1

    return input_operands


def calculate_metrics(tokens):

    operators = []
    operands = []

    for token_type, value in tokens:

        if token_type == "OPERATOR":
            operators.append(value)

        elif token_type == "OPERAND":
            operands.append(value)

    # Total occurrences
    N1 = len(operators)
    N2 = len(operands)

    # Distinct operators and operands
    unique_operators = set(operators)
    unique_operands = set(operands)

    eta1 = len(unique_operators)
    eta2 = len(unique_operands)

    # Actual Program Length
    N = N1 + N2

    # Estimated Program Length
    Ne = (
        (eta1 * math.log2(eta1) if eta1 > 0 else 0)
        + (eta2 * math.log2(eta2) if eta2 > 0 else 0)
    )

    # Program Volume
    V = N * math.log2(eta1 + eta2) if eta1 + eta2 > 1 else 0

    # Actual input operands
    input_operands = find_input_operands(tokens)
    eta2_star = len(input_operands)

    # Critical Volume
    Vc = (2 + eta2_star) * math.log2(2 + eta2_star)

    # Program Level
    L = Vc / V if V != 0 else 0

    # Program Effort
    E = V / L if L != 0 else 0

    return {
        "operators": operators,
        "operands": operands,
        "unique_operators": unique_operators,
        "unique_operands": unique_operands,
        "input_operands": input_operands,
        "N1": N1,
        "N2": N2,
        "eta1": eta1,
        "eta2": eta2,
        "N": N,
        "Ne": Ne,
        "V": V,
        "eta2_star": eta2_star,
        "Vc": Vc,
        "L": L,
        "E": E
    }


def main():

    filename = input("Enter source file name (.txt): ")

    try:

        with open(filename, "r", encoding="utf-8") as file:
            code = file.read()

    except FileNotFoundError:

        print("File not found!")
        return

    # Lexical analysis using transition diagram
    (
        tokens,
        invalid_identifiers,
        invalid_constants,
        invalid_operators
    ) = transition_diagram(code)

    result = calculate_metrics(tokens)

    print("\n========== TOKEN ANALYSIS ==========")

    print("\nOperators:")
    print(result["operators"])

    print("\nOperands:")
    print(result["operands"])

    print("\nUnique Operators:")
    print(sorted(result["unique_operators"]))

    print("\nUnique Operands:")
    print(sorted(result["unique_operands"]))

    print("\nInput Operands:")
    print(sorted(result["input_operands"]))

    print("\n========== HALSTEAD METRICS ==========")

    print("N1  (Total Operators)       :", result["N1"])
    print("N2  (Total Operands)        :", result["N2"])

    print("η1  (Unique Operators)      :", result["eta1"])
    print("η2  (Unique Operands)       :", result["eta2"])

    print("N   (Actual Length)         :", result["N"])
    print("Ne  (Estimated Length)      :", round(result["Ne"], 4))

    print("V   (Program Volume)        :", round(result["V"], 4), "bits")

    print("η2* (Input Operands)        :", result["eta2_star"])
    print("Vc  (Critical Volume)       :", round(result["Vc"], 4), "bits")

    print("L   (Program Level)         :", round(result["L"], 6))
    print("E   (Program Effort)        :", round(result["E"], 4), "bits")

    print("\n========== INVALID ENTITIES ==========")

    print("Invalid Identifiers :", invalid_identifiers)
    print("Invalid Constants   :", invalid_constants)
    print("Invalid Operators   :", invalid_operators)

    if not (
        invalid_identifiers
        or invalid_constants
        or invalid_operators
    ):
        print("No invalid entities found.")


if __name__ == "__main__":
    main()