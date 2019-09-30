// Finds longest substring S[i..] = S[0..] and stores its length as Z[i].
// i.e. Z[i] is the longest substring starting from i which is also a prefix.
// Runtime O(N), where N = S.length().
// Source: http://codeforces.com/blog/entry/3107
#include <iostream>
#include <vector>
using namespace std;

vector<int> computeZ(string s)
{
	int L=0, R=0, n=s.length();
	//loop invariant : [L, R] matches [0, R-L].
	vector<int> z(s.length());
	for (int i = 1; i < n; i++) 
	{
		if (i > R) 
		{
			L = R = i;
			while (R < n && s[R-L] == s[R]) //while Rth and R-L th char match.
				R++;						//Keep incrementing R.
			z[i] = R-L;						//s[i, R) match s[0, R-i)
			R--;							//now, s[i, R]==s[0, R-i]
		} 
		else 
		{
			int k = i-L;
			if (z[k] < R-i+1) 				//s[k, R] doesn't match s[0, R-k].
				z[i] = z[k];
			else 
			{
				L = i;
				while (R < n && s[R-L] == s[R]) 
					R++;
				z[i] = R-L; 
				R--;
			}
		}
	}
	return z;
}

int main()
{
	string s;
	cin>>s;
	vector<int> zValues = computeZ(s);
	for(size_t i=0; i<s.length(); i++)
	{
		cout << i<<' '<<zValues[i]<<endl;
	}
}