
def search_replace(text, pattern, replacement):
    if pattern not in text:
        print("Pattern not found")
        return text

    result = ""
    i = 0

    while i < len(text):
        if text[i:i + len(pattern)] == pattern:
            result += replacement
            i += len(pattern)
        else:
            result += text[i]
            i += 1

    return result


text = input("Enter text: ")
pattern = input("Enter pattern to search: ")
replacement = input("Enter replacement: ")

result = search_replace(text, pattern, replacement)

print("Result:", result)
