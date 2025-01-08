def is_sentence(word):
    return word.endswith((".", "!", "?"))

def count_letters(word):
    return sum(1 for char in word if char.isalpha())

def readability():
    text = input("Text: ")
    words = text.split()
    words_length = len(words)
    letters = 0
    sentences = 0
    for word in words:
        letters += count_letters(word)
        if is_sentence(word):
            sentences += 1

    average_letters = letters / words_length * 100
    average_sentences = sentences / words_length * 100
    grade = 0.0588 * average_letters - 0.296 * average_sentences - 15.8
    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade: {round(grade)}")

if __name__ == '__main__':
    readability()
