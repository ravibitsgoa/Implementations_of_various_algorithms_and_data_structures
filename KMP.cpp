//This implements Knuth-Morris-Pratt String matching algorithm.
//Runtime O(T+P) where T= length of Text, P= length of Pattern
//Source: https://www.topcoder.com/community/data-science/data-science-tutorials/introduction-to-string-searching-algorithms/
#include <iostream>
#include <vector>
using namespace std;

// The prefix under index i in the automaton below, 
// is the string from pattern[0] to pattern[i - 1] 
// inclusive, so the last character of the string under 
// index i is pattern[i - 1].
vector<int> build_automaton(const string& pattern)
{   
    int m= pattern.length();
    vector<int> automaton(m+1, 0);
    automaton[0] = automaton[1] = 0;    //always true
    
    for(int i = 2; i <= m; i++) 
    {
        // j is the index of the largest next partial match 
        // (the largest suffix/prefix) of the string under  
        // index i - 1
        int j = automaton[i - 1];
        do
        {   
            // check to see if the last character of string i - pattern[i - 1]
            // "expands" the current "candidate"
            // best partial match -> the prefix under index j
            if(pattern[j] == pattern[i - 1]) 
            {   automaton[i] = j + 1; 
                break; 
            }
            // else go to the next best "candidate" partial match
            j = automaton[j];
        } while(j>0);
        // if we cannot "expand" even the empty string, 
        // automaton[i] is by default 0.
    }
    return automaton;
}

bool Knuth_Morris_Pratt(const string& text, const string& pattern)
{
	int n= text.length(), m=pattern.length();
	vector<int> automaton = build_automaton(pattern);
	int state_of_automaton = 0;
	
	for(int current_char = 0; current_char<n; current_char++)
	{
		do
		{	
			// if the current character of the text "expands" the
			// current match
			if(text[current_char] == pattern[state_of_automaton])
			{
				state_of_automaton++;
				if(state_of_automaton == m)	//match found.
					return true;
				break;						//go to next character.
			}

			// if we reached the empty string and failed to
			// "expand" even it; we go to the next 
			// character from the text, the state of the
			// automaton remains zero
			if(state_of_automaton == 0)
				break;
				
			// if the current state is not zero (we have not
			// reached the empty string yet) we try to
			// "expand" the next best (largest) match			
			state_of_automaton = automaton[state_of_automaton];
		}	while(state_of_automaton >= 0); 
		
	}
	return false;
}

int main()
{   
    string text="ababacb", pattern="ababac";
    vector<int> autom = build_automaton(pattern);
    for(int i: autom)
		cout << i<<endl;
	cout << Knuth_Morris_Pratt(text, pattern);
}
