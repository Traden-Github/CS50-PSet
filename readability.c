#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    double l = count_letters(text);
    double w = count_words(text);
    double s = count_sentences(text);

    int index = round(0.0588 * ((l / w) * 100.0) - 0.296 * ((s / w) * 100.0) - 15.8);
    if (index >= 1 && index < 16)
    {
        printf("Grade %i\n", index);
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Before Grade 1\n");
    }
}

int count_letters(string text)
{
    int letter_count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (islower(text[i]) || isupper(text[i]))
        {
            letter_count++;
        }
    }
    return letter_count;
}

int count_words(string text)
{
    int word_by1 = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            word_by1++;
        }
    }
    word_by1++;
    return word_by1;
}

int count_sentences(string text)
{
    int sentence_count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentence_count++;
        }
    }
    return sentence_count;
}
