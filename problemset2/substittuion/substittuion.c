#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

string encrypt(string, string);
int index(char);
string lower(string);
int validate_is_alphabet(string);
int validate_input(string, int);
int ALPHABET_LENGTH = 26;


int main(int argc, string argv[])
{
    if (validate_input(argv[1], argc) == 1)
    {
        return 1;
    }

    if (validate_is_alphabet(argv[1]) == 1)
    {
        return 1;
    }

    string plaintext = get_string("plaintext:  ");
    string ciphertext = encrypt(plaintext, argv[1]);

    printf("ciphertext: %s\n", ciphertext);

}


string encrypt(string text, string key)
{
    int lenght = strlen(text);
    int position;

    for (int i = 0; i < lenght; i++)
    {
        if (isalpha(text[i]) != 0)
        {
            position = index(text[i]);

            if (islower(text[i]) != 0)
            {
                text[i] = tolower(key[position]);
            }
            else
            {
                text[i] = toupper(key[position]);
            }
        }
    }
    return text;
}


int index(char letter)
{
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int position;

    for (int i = 0; i < ALPHABET_LENGTH ; i++)
    {
        if (tolower(letter) == alphabet[i])
        {
            position = i;
        }
    }
    return position;
}


int validate_is_alphabet(string key)
{
    int count_letters[ALPHABET_LENGTH];

    for (int i = 0; i < ALPHABET_LENGTH; i++)
    {
        count_letters[tolower(key[i]) - 'a']++;
    };

    for (int i = 0; i < ALPHABET_LENGTH; i++)
    {
        if (count_letters[i] ==! 1)
        {
            printf("Key has duplicate letters.\n");
            return 1;
        };
    };
    return 0;
}


int validate_input(string key, int argc)
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(key) != ALPHABET_LENGTH)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int i = 0; i < ALPHABET_LENGTH ; i++)
    {
        if (isalpha(key[i]) == 0)
        {
            printf("only letters of the alphabet\n");
            return 1;
        }
    }
    return 0;
}
