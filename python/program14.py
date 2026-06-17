class TextAnalyzer:
    def __init__(self, text):
        self.text = text

    @classmethod
    def is_palindrome(cls, word):
        """Class method to check if a single word reads the same backwards."""
        # Convert to lowercase to ensure the check is case-insensitive
        cleaned_word = word.lower()
        return cleaned_word == cleaned_word[::-1] and len(cleaned_word) > 1

    def find_unique_and_palindromes(self):
        """String method that processes the instance's text."""
        # 1. Clean the string text (remove basic punctuation and lowercase it)
        cleaned_text = "".join(char.lower() for char in self.text if char.isalnum() or char.isspace())
        
        # 2. Get unique words using a Python set
        words = cleaned_text.split()
        unique_words = set(words)
        
        # 3. Filter the unique words using our class method palindrome checker
        # We invoke the class method using self.is_palindrome or TextAnalyzer.is_palindrome
        palindromes = [word for word in unique_words if self.is_palindrome(word)]
        
        return list(unique_words), palindromes


# --- Demonstration ---
sample_text = "Madam went to buy a racecar, but she forgot her wallet. Wow, what a day!"

# Initialize the object with the text string
analyzer = TextAnalyzer(sample_text)

# Run the string processing method
unique_list, palindrome_list = analyzer.find_unique_and_palindromes()

print("--- Analysis Results ---")
print(f"Unique Words Found:\n{unique_list}\n")
print(f"Palindromes Found:\n{palindrome_list}")