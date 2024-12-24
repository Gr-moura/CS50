from cs50 import get_string

def main():
    # Get user input
    text = get_string("Text: ")

    # Count the number of letters, words, and sentences
    letters = 0
    words = 1
    sentences = 0

    for c in text:
        if c.isalpha():
            letters += 1
        elif c.isspace():
            words += 1
        elif c in [".", "!", "?"]:
            sentences += 1

    # Calculate the Coleman-Liau index
    L = letters / words * 100
    S = sentences / words * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # Print the grade level
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")    


if __name__ == "__main__":
    main()