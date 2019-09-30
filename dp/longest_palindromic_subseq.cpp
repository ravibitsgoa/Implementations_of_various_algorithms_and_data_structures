//https://www.geeksforgeeks.org/dynamic-programming-set-12-longest-palindromic-subsequence/
#include <iostream>
#include <algorithm>
using namespace std;

int LPS(string &x, int l, int r, vector<vector<int> > &dp)
{
    if(dp[l][r] != -1)
        return dp[l][r];

    if(l == r-1)
        dp[l][r] = 1;
    else if(l>=r)
        return 0;
    else if(s[l] == s[r-1])
        dp[l][r] = 2 + LPS(x, l+1, r-1);
    else
        dp[l][r] = max(LPS(x, l+1, r), LPS(x, l, r-1));
    return dp[l][r];
}

int main()
{
    string x = "MAHDYNAMICPROGRAMZLETMESHOWYOUTHEM";
    //expected LPS : "MHYMRORMYHM". length = 11.
    vector<vector<int> > dp(n+1, vector<int> (n+1, -1));
    cout << LPS(x, 0, x.length(), dp);
}
