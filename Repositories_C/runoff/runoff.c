#include <cs50.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100 // 选民上界
#define MAX_CANDIDATES 9 // 候选人上界

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES]; 

// Candidates have name, vote count, eliminated status
typedef struct{
    string name;
    int votes;
    bool eliminated;
} candidate;//candidate just like "int, void, bool", we can candidate something, but doesn't take the data. So we can't write candidate.name. If I want to take the data, I must write candidates.name, which is an array we defined.

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[]){
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    // 如果大于我们设定的上界，则退出
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }

    // Save state, which is saved candidates' name, vote(0), eliminated. So we can use them later.
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false; // 淘汰状态
    }

    voter_count = get_int("Number of voters: "); 

    // 同上
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++){

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
    while (true){
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

        // Reset vote counts back to zero. Why? Because we save the preference, but we need to clear the data this time, if we don't clear, there is no one be eliminated. And in the while, we will put the eliminated one's votes to others.
        for (int i = 0; i < candidate_count; i++){
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name){
  for(int k=0; k < candidate_count; ++k){
    if(strcmp(candidates[k].name, name) == 0){
      preferences[voter][rank] = k;
      return true;
    }
  }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void){
  for(int i = 0; i < voter_count; ++i){
    for(int j = 0; j < candidate_count; ++j){
      int k = preferences[i][j];

      if(!candidates[k].eliminated){
	++candidates[k].votes;
	break;
      }
    }
  }
}

// Print the winner of the election, if there is one
bool print_winner(void){
  for(int i=0; i<candidate_count; ++i){
    if(candidates[i].votes > voter_count / 2){
      printf("The winner is %s.\n", candidates[i].name);
	return true; 
    }
  }
  return false;
}//what status? If no one's votes are more than half, the program return false, and we need to count again.  
 
// Return the minimum number of votes any remaining candidate has
int find_min(void){
  int min_votes = INT_MAX;
  
  for(int i=0; i<candidate_count; ++i){
    if(!candidates[i].eliminated &&
       candidates[i].votes < min_votes)
      min_votes = candidates[i].votes;
  }
  return min_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min){
  for(int i=0; i<candidate_count; ++i){
    if(!candidates[i].eliminated &&
       candidates[i].votes != min){
      return false;
    }
  }
  return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min){ //传入最小值，将最小值与候选人的数据结构相匹配(for(every candidates)if(candidates[i].votes == min))，将这个候选人的 eliminated 设置为 true(candidates[i].eliminated = true), 不需要返回值。
  for(int i=0; i<candidate_count; ++i){
    if(candidates[i].votes == min){
      candidates[i].eliminated = true;
    }
  }
}
