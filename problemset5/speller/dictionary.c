// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

void free_node(struct node *node_word);
// TODO: Choose number of buckets in hash table
const unsigned int N = 650;

// Hash table
node *table[N];

//size
unsigned int size_dictionary = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *node_start = table[hash(word)];
    for (node *node_word = node_start; node_word != NULL; node_word = node_word->next)
    {
        if (node_word == NULL)
        {
            return false;
        }
        if (strcasecmp(node_word->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    if (strlen(word) == 1)
    {
        return (toupper(word[0]) - 'A') * 25;
    }
    else
    {
        return (toupper(word[0]) - 'A') * 25 + toupper(word[1]) - 'A';
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    char letter;
    node *new_node = malloc(sizeof(node));
    int length_word = 0;

    while (fread(&letter, sizeof(char), 1, file))
    {

        if (letter == '\n')
        {
            new_node->word[length_word] = '\0';
            unsigned int hash_word = hash(new_node->word);
            if (table[hash_word] == NULL)
            {
                new_node->next = NULL;
                table[hash_word] = new_node;
            }
            else
            {
                node *node_list = table[hash_word];
                new_node->next = node_list;
                table[hash_word] = new_node;
            }
            new_node = malloc(sizeof(node));
            size_dictionary++;
            length_word = 0;
        }
        else
        {
            new_node->word[length_word] = letter;
            length_word++;
        }
    }
    fclose(file);
    free(new_node);
    return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return size_dictionary;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            free_node(table[i]);
        }
    }
    return true;
}

void free_node(struct node *node_word)
{
    if (node_word == NULL)
    {
        return;
    }
    else {

        free_node(node_word->next);
        free(node_word);
    }
}
