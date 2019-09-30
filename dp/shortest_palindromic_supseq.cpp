//http://jeffe.cs.illinois.edu/teaching/algorithms/notes/05-dynprog.pdf
//most of the questions of this dp folder are exercises from this PDF.
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//#define PRINT_ALL_SUB

int SPS(const string &x, int l, int r, vector<vector<int> > &dp)
{
	if(dp[l][r] != -1)
		return dp[l][r];

	if(l == r-1)
		dp[l][r] = 1;
	/*else if(l == r-2)
	{
		if(x[l] == x[r-1])
			dp[l][r] = 2;
		else
			dp[l][r] = 3;
	}*/
	else if(l>=r)
		return 0;
	else if(x[l] == x[r-1])
		dp[l][r] = 2 + SPS(x, l+1, r-1, dp);
	else
		dp[l][r] = 2 + min(SPS(x, l+1, r, dp), SPS(x, l, r-1, dp));

	return dp[l][r];
}

int main()
{
	string x = "TWENTYONE";
	int n = x.length();
	//expected LPS : "TWENTOYOTNEWT". length = 13.
	vector<vector<int> > dp(n+1, vector<int> (n+1, -1));
	cout << x << endl << SPS(x, 0, x.length(), dp) << endl;

#ifdef PRINT_ALL_SUB
	cout << ' ';
	for(int j=0; j<=n; j++)
		cout << j <<'\t';
	cout << endl;
	for(int i=0; i<=n; i++)
	{
		cout << endl;
		cout << i << '\n';
		for(int j=0; j<=n; j++)
			 cout << dp[i][j] << '\t';
	}
#endif

}
