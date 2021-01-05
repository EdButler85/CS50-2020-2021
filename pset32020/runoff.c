#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
int get_index(string name);
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}


// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Iterating through number of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Checking vote name is a match with the candiate name in location i
        if (!strcmp(name, candidates[i].name))
        {
                
            // Updating the global preferences array with the rank of the voted candidate
            preferences[voter][rank] = i;
            return true;
            break;
        }
    }

    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Iterate over number of voters
    for (int i = 0; i < voter_count; i++)
    {
        // Iterate over number of candidates
        for (int j = 0; j < candidate_count; j++)
        {
            // Checking to see if each voted-for candidate has been eliminated
            if (candidates[preferences[i][j]].eliminated == false)
            {
                // Incrementing the vote count
                candidates[preferences[i][j]].votes++;
                break;
            }
        }
        
    }

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    bool winner = false;
    float goal = (voter_count / 2);
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes > goal)
        {
            winner = true;
            printf("The Winner is ...%s\n", candidates[i].name);
            return winner;
        }
    }
    return winner;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = voter_count;
    for (int g = 0; g < candidate_count; g++)
    {
        // Checking if a candidate is not eliminates, and has fewer than the min number of votes
        if (candidates[g].eliminated == false && candidates[g].votes < min)
        {
            min = candidates[g].votes;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int cand_not_elim = 0;
    int votes_at_minimum = 0;
    
    for (int q = 0; q < candidate_count; q++)
    {
        // Checking if the candidate is eliminated, , and logging with local variable
        if (candidates[q].eliminated == false)
        {
            cand_not_elim++;
        }
    }
    // Iterating over candidates and checking if they have "minimum votes""
    for (int w = 0; w < candidate_count; w++)
    {
        if (candidates[w].votes == min)
        {
            votes_at_minimum++;
        }
    }
    if (votes_at_minimum == cand_not_elim)
    {
        return true;
    }
    return false;
}


// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    for (int e = 0; e < candidate_count; e++)
    {
        if (candidates[e].eliminated == false && (candidates[e].votes == min))
        {
            candidates[e].eliminated = true;
        }
    }
    return;
}