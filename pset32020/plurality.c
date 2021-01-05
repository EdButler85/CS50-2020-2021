#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    bool valid_vote = false;

    // Iterating through number of candidates and comparing string "name" to get a boolean result.
    for (int i = 0; i < candidate_count; i++)
    {

        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            valid_vote = true;

            // Force a break in the program to exit with the correct result
            break;
        }
    }
    return valid_vote;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Initialising a variable for the most votes, and the candidate
    int highest_votes = -1;

    // Looping through results and finding the highest "votes" value
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > highest_votes)
        {
            highest_votes = candidates[i].votes;
        }
    }

    if (highest_votes == -1)
    {
        printf("No Winner\n");
        return;
    }

    // Comparing all "votes" values and printing winner(s)
    for (int j = 0; j < candidate_count; j++)
    {
        if (highest_votes == candidates[j].votes)
        {
            printf("%s\n", candidates[j].name);
        }
    }
}
