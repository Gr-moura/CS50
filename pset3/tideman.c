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
} pair;

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

int get_candidatePos(string name)
{
    for (int candidatePos = 0; candidatePos < candidate_count; candidatePos++)
    {
        if (strcmp(name, candidates[candidatePos]) == 0)
        {
            return candidatePos;
        }
    }

    return -1;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    int candidatePos = get_candidatePos(name);

    if (candidatePos == -1)
        return false;

    ranks[rank] = candidatePos;

    return true;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;

    // We compare
    for (int i = 1; i < candidate_count; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            if (preferences[i][i - j] == preferences[i - j][i])
                continue;

            if (preferences[i][i - j] > preferences[i - j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = i - j;
                pair_count++;

                continue;
            }

            if (preferences[i][i - j] < preferences[i - j][i])
            {
                pairs[pair_count].winner = i - j;
                pairs[pair_count].loser = i;
                pair_count++;

                continue;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            int strength1 = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            int strength2 = preferences[pairs[j + 1].winner][pairs[j + 1].loser] - preferences[pairs[j + 1].loser][pairs[j + 1].winner];
            if (strength1 < strength2)
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
}

// Check if locking a pair creates a cycle
bool isLooping(int winner, int loser)
{
    if (locked[loser][winner])
        return true;

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (isLooping(winner, i))
                return true;
        }
    }

    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int pairIndex = 0; pairIndex < pair_count; pairIndex++)
    {
        if (isLooping(pairs[pairIndex].winner, pairs[pairIndex].loser))
            continue;

        locked[pairs[pairIndex].winner][pairs[pairIndex].loser] = true;
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool isWinner = true;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                isWinner = false;
                break;
            }
        }

        if (isWinner)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }

    return;
}
