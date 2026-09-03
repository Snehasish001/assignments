class Lexer:
    def __init__(self, text: str):
        self.text = text
        self.pos = 0
        self.length = len(text)
        self.keywords = {"if", "for", "while", "int", "float", "char"}
        self.operators = {"+", "-", "*", "/", "=", "<", ">"}
        self.symbols = {"{", "}", "(", ")", ";", "?", ","}

    def tokenize(self):
        tokens = []

        while self.pos < self.length:
            char = self.text[self.pos]

            if char.isspace():
                self.pos += 1
                continue

            if char.isalpha():
                token_type, value = self._match_identifier_or_keyword()
                tokens.append((token_type, value))

            elif char.isdigit():
                token_type, value = self._match_constant()
                tokens.append((token_type, value))

            elif char in self.operators:
                tokens.append(("Operator", char))
                self.pos += 1

            elif char in self.symbols:
                tokens.append(("Symbol", char))
                self.pos += 1

            else:
                tokens.append(("ERROR", f"Invalid character '{char}'"))
                self.pos += 1

        return tokens

    def _match_identifier_or_keyword(self):
        start_pos = self.pos
        self.pos += 1

        while self.pos < self.length and (
            self.text[self.pos].isalnum() or self.text[self.pos] == "_"
        ):
            self.pos += 1

        lexeme = self.text[start_pos : self.pos]

        if lexeme in self.keywords:
            return ("Keyword", lexeme)

        if len(lexeme) <= 8:
            return ("Identifier", lexeme)
        else:
            return ("ERROR", f"Identifier '{lexeme}' exceeds 8 characters")
        
    def _match_constant(self):
        start_pos = self.pos

        while self.pos < self.length and self.text[self.pos].isdigit():
            self.pos += 1

        lexeme = self.text[start_pos : self.pos]
        val = int(lexeme)

        if 1 <= val <= 999 and not (len(lexeme) > 1 and lexeme.startswith("0")):
            return ("Constant", lexeme)
        else:
            return (
                "ERROR",
                f"Constant '{lexeme}' out of valid range (1-999) or has leading zero",
            )


def main():
    code = ""
    with open('input.txt', 'r', encoding='utf-8') as file:
        code = file.read()
    lexer = Lexer(code)
    tokens = lexer.tokenize()

    print("--- TOKEN CLASSIFICATION RESULT ---")
    has_errors = False

    for token_type, value in tokens:
        if token_type == "ERROR":
            print(f"[ERROR]      : {value}")
            has_errors = True
        else:
            print(f"{token_type:<12} : {value}")

    if has_errors:
        print("\nExecution stopped due to token errors.")


if __name__ == "__main__":
    main()