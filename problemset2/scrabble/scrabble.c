#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);
void print_winner(int, int);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    print_winner(score1, score2);
}

int compute_score(string word)
{
    int sum = 0;
    int value;
    // if letter is lower letter - 97 is value to acess POINTS
    int LOWER_ASCII = 97;
    // if letter is upper letter - 65 is value to acess POINTS
    int UPPER_ASCII = 65;
    for (int i = 0; i < strlen(word); i++)
    {
        if (ispunct(word[i]))
        {
            continue;
        }
        else if (isupper(word[i]))
        {
            value = word[i] - UPPER_ASCII;
        }
        else if (islower(word[i]))
        {
            value = word[i] - LOWER_ASCII;
        }
        sum += POINTS[value];
    }
    return sum;
}

void print_winner(int score1, int score2)
{
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!");
    }
}
