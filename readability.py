def main():
    text = input("Text: ")
    l = count_letters(text)
    w = count_words(text)
    s = count_sentences(text)

    index = round(0.0588 * ((l / w) * 100) - 0.296 * ((s / w) * 100) - 15.8)

    if 1 <= index < 16:
        print(f"Grade {index}")
    elif index >= 16:
        print("Grade 16+")
    else:
        print("Before Grade 1")


def count_letters(text):
    letterCount = 0
    for letter in text:
        if letter.isalpha() == True:
            letterCount += 1
    return letterCount


def count_words(text):
    word_by_1 = 0
    for letter in text:
        if letter == " ":
            word_by_1 += 1
    word = word_by_1 + 1
    return word


def count_sentences(text):
    sentence = 0
    for letter in text:
        match letter:
            case "." | "?" | "!":
                sentence += 1
    return sentence


if __name__ == "__main__":
    main()
