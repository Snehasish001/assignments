from collections import Counter

class TextAnalyzer:
    def __init__(self, text):
        self.text = text
        self.words = text.split()

    def __len__(self):
        freq = Counter(self.words)

        repeated_words = [word for word, count in freq.items()
                          if count > 1]

        if repeated_words:
            return sum(len(word) for word in repeated_words)

        return len(self.text)

    def most_frequent(self):
        freq = Counter(self.words)
        return freq.most_common()



text = input("Enter a text: ")

obj = TextAnalyzer(text)

print("\nLength using len():", len(obj))

print("\nWord Frequencies:")
for word, count in obj.most_frequent():
    print(f"{word} -> {count}")