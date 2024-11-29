#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string, int);
int count_words(string, int);
int count_sentences(string, int);
void index_coleman(int, float, int);

int main(void)
{
    string text = get_string("Text: ");
    int lenght = strlen(text);

    int letters = count_letters(text, lenght);
    int words = count_words(text, lenght);
    int sentences = count_sentences(text, lenght);

    index_coleman(letters, (float) words, sentences);

}


int count_letters(string text, int lenght)
{
    int letters = 0;
    for (int i = 0; i < lenght; i++)
    {
        if (isalpha(text[i]) != 0)
        {
            letters++;
        }
    }
    return letters;
}


int count_words(string text, int lenght)
{
    int words = 1;
    for (int i = 0; i < lenght; i++)
    {
        if (isspace(text[i]) != 0)
        {
            words++;
        }
    }
    return words;
}


//count sentences
int count_sentences(string text, int lenght)
{
    int sentences = 0;
    for (int i = 0; i < lenght; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}


//calculate Coleman-Liau index
void index_coleman(int letters, float words, int sentences)
{
    float average_letters = letters / words * 100 ;

    double average_sentences = sentences / words * 100;

    int index = round(0.0588 * average_letters - 0.296 * average_sentences - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }

}
