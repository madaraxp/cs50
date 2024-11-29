#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX_CANDIDATES 9

typedef struct
{
    string name;
    int votes;
} Candidate;

Candidate candidates[MAX_CANDIDATES];
int candidate_count;

// Function prototypes
bool vote(string);
void print_winner();
int validate_input(int);

int main(int argc, string argv[])
{

    candidate_count = argc - 1;

    if (validate_input(argc) != 0)
    {
        return 1;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    print_winner();
}

int validate_input(int argc)
{
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    return 0;
}

bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

void print_winner()
{
    int max = 0;

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (candidates[j].votes > max)
            {
                max = candidates[j].votes;
            }
            if (i == 1 && candidates[j].votes == max)
            {
                printf("%s\n", candidates[j].name);
            }
        }
    }

    return;
}
