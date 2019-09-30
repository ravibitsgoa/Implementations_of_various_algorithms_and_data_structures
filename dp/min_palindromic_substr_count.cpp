//problem 8c : http://jeffe.cs.illinois.edu/teaching/algorithms/notes/05-dynprog.pdf
#include <vector>
#include <algorithm>
#include <iostream>
//#define VERBOSE
using namespace std;

/* returns true if x[l, r) is a palindrome.
 **/
bool is_palin(const string &x, int l, int r)
{
    for(int i=l, j=r-1; i<j; i++, j--)
    {
        if(x[i] != x[j])
            return false;
    }
    return true;
}

/* returns min number of palindromes x[l, r) can be partitioned in.
 * modifies dp vector if x[l, r) itself is not a palindrome.
 **/
int palin_count(const string &x, int l, int r, vector<vector<int> > &dp,
                vector<vector<int> > &js)
{
    if(dp[l][r] != -1)
        return dp[l][r];
    if(l>=r)
        return 0;
    if(l == r-1)
        return 1;

    if(is_palin(x, l, r))
    {
        return 1;
    }

    int count = r-l;
    int jmin=l;
    for(int j=l+1; j<r; j++)
    {
        int old = count;
        count = min(count, palin_count(x, l, j, dp, js) + palin_count(x, j, r, dp, js) );
        if(count < old)
        {
            jmin = j;
        }
    }
    dp[l][r] = count;
    js[l][r] = jmin;
    return count;
}

/* prints partition of x[l, r) into palindrome substrings.
 **/
void print_partition(   const string &x, int l, int r,
                        const vector<vector<int> > &dp,
                        const vector<vector<int> > &parts)
{
    if(l == r-1)
    {
        cout << x[l];
    }
    else if(l>=r)
    {
        return;
    }
    else if(parts[l][r] == -1)  //x[l..r] is itself a palindrome.
    {
        for(int i=l; i<r; i++)
            cout << x[i];
    }
    else
    {
        print_partition(x, l, parts[l][r], dp, parts);
        cout << " | ";
        print_partition(x, parts[l][r], r, dp, parts);
    }
}

int main()
{
    string x = "BUBBASEESABANANA";
    //expected output : 3 (BUB BASEESAB ANANA)
    int n = x.length();
    vector<vector<int> > dp(n+1, vector<int> (n+1, -1));        //dp[i][j]= min number of palindromes in x[i, j)
    vector<vector<int> > partition(n+1, vector<int> (n+1, -1)); //partition[i][j] = any one index that partitions palindromes.
    cout << x << endl << palin_count(x, 0, x.length(), dp, partition) << endl;

#ifdef VERBOSE    //enable this to print all details of partitions and palindrome counts.
	cout << ' ';
	for(int j=0; j<=n; j++)
		cout << j <<'\t';
	cout << endl;
	for(int i=0; i<=n; i++)
	{
		cout << endl;
		cout << i << '\n';
		for(int j=0; j<=n; j++)
			 cout << dp[i][j] << ' ' << partition[i][j] << ' ' << '\t';
	}
#endif

    print_partition(x, 0, x.length(), dp, partition);
}
