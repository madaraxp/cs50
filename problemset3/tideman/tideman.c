#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cyrcle(int winner, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    bool valid_name = false;
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            valid_name = true;
            ranks[rank] = i;
            break;
        }
    }
    return valid_name;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            if (i == j)
            {
                preferences[i][j] = 0;
            }else{

                preferences[ranks[i]][ranks[j]] += 1;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            if (j != i)
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].loser = j;
                    pairs[pair_count].winner = i;
                    pair_count = pair_count + 1;
                }
                else if (preferences[j][i] > preferences[i][j])
                {
                    pairs[pair_count].loser = i;
                    pairs[pair_count].winner = j;
                    pair_count = pair_count + 1;
                }

            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for ( int j = 0; j < pair_count; j++)
    {

        int max_votes = 0;
        pair more_votes;
        int position;
        pair save;
        for ( int i = j; i < pair_count; i++)
        {
            int winner = pairs[i].winner;
            int loser = pairs[i].loser;
            int votes = preferences[winner][loser];
            if (votes > max_votes)
            {
                max_votes = votes;
                more_votes = pairs[i];
                position = i;
            }
        }
        save = pairs[j];
        pairs[j] = pairs[position];
        pairs[position] = save;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int loser = pairs[i].loser;
        int winner = pairs[i].winner;
        bool win;
        win = cyrcle(winner, loser);
        if (!win)
        {
            locked[winner][loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int winner;
    int loses = candidate_count;
    for (int i = 0; i < candidate_count; i++)
    {
        int number_defeats = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                number_defeats = number_defeats + 1;
            }
        }
        if (number_defeats <= loses )
        {
            loses = number_defeats;
            winner = i;
        }
    }
    printf("%s\n", candidates[winner]);
    return;
}

bool cyrcle(int winner, int loser)
{
    if (winner == loser)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (cyrcle(winner, i))
            {
                return true;
            }
        }
    }
    return false;
}