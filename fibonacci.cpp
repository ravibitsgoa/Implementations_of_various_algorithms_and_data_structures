//This finds Nth term of Fibonacci series in O(logN * loglogN) time.
//Source: http://codeforces.com/blog/entry/14516, thanks to kien_coi_1997
// based on: 	f(2 * k) 			= f(k) * f(k) + f(k - 1) * f(k - 1).
//     				f(2 * k + 1) 	= f(k) * f(k + 1) + f(k - 1) * f(k).

#include <map>
#include <iostream>
using namespace std;

#define long long long			//KEEP IN MIND...

const long M = 1000000007; 	// modulo, AKA 1e9 + 7.
map<long, long> F;

long f(long n)
{	if (F.count(n)) return F[n];
	long k=n/2;
	if (n%2==0)
	{ // n=2*k
		return F[n] = (f(k)*f(k) + f(k-1)*f(k-1)) % M;
	}
	else
	{ // n=2*k+1
		return F[n] = (f(k)*f(k+1) + f(k-1)*f(k)) % M;
	}
}

int main()
{	long n;
	F[0]=F[1]=1;
	while (cin >> n)
		cout << (n==0 ? 0 : f(n-1)) << endl;
	return 0;
}
