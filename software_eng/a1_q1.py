
def justify_text(text, width, indent=4):
    words = text.split()
    lines = []
    current = []
    current_len = 0
    first_line = True

    for word in words:
        limit = width - indent if first_line else width

        if current_len + len(word) + len(current) <= limit:
            current.append(word)
            current_len += len(word)
        else:
            # Justify the current line
            if len(current) == 1:
                line = current[0]
            else:
                spaces = limit - current_len
                gaps = len(current) - 1
                extra = spaces % gaps
                base = spaces // gaps

                line = ""
                for i in range(gaps):
                    line += current[i] + " " * (base + (1 if i < extra else 0))
                line += current[-1]

            if first_line:
                line = " " * indent + line

            lines.append(line)

            current = [word]
            current_len = len(word)
            first_line = False

    # Last line: left justified
    if current:
        line = " ".join(current)
        if first_line:
            line = " " * indent + line
        lines.append(line)

    return "\n".join(lines)


text = "Python is a powerful programming language used for artificial intelligence machine learning and web development"

print(justify_text(text, 30))
