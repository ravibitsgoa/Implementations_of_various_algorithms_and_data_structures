//https://www.geeksforgeeks.org/find-number-times-string-occurs-given-string/
int count(const string &x, const string &y, int n, int m, vector<vector<int> > dp)
{
    if(dp[n][m] != -1)
        return dp[n][m];

    if(x[n-1] == y[m-1])
        dp[n][m]= (1 + count(x, y, n-1, m-1));
    else
    {
        dp[n][m] = max(count(x, y, n-1, m), count(x, y, n, m-1));
    }
    return dp[n][m];
}

int main()
{
    string x = "helo";
    string y = "helo abcd helo abcd";
    vector<vector<int> > dp(n, vector<int> (m, -1) );
    cout << count(x, y, x.length(), y.length(), dp);
}
