//This finds Nth term of Fibonacci series in O(logN * loglogN) time.
//Source: http://codeforces.com/blog/entry/14516, thanks to kien_coi_1997
// based on: 	f(2 * k) 			= f(k) * f(k) + f(k - 1) * f(k - 1).
//     				f(2 * k + 1) 	= f(k) * f(k + 1) + f(k - 1) * f(k).

#include <unordered_map>
#include <iostream>
using namespace std;

const long long MOD = 1000000007; 	// modulo, AKA 1e9 + 7.
unordered_map<long long, long long> F;

long long f(long long n)
{	if (F.count(n)) return F[n];
	long long k=(n>>1);
	if (!(n&1))// n= 2k
	{
        long long temp1 = f(k);
        long long temp2 = f(k-1);
        F[n] = ((temp1*temp1 + temp2*temp2) % MOD);
        return F[n];
    }
	else       // n = 2k+1
	{
        long long temp = f(k);
		F[n] = (temp*f(k+1) + f(k-1)*temp) % MOD;
        return F[n];
    }
}

/* The following one does the same thing using matrix exp.
*/
void power(long long mat[2][2], long long n)
{
	if(n==0)	//any matrix raised to power 0 is Identity matrix. [1 0; 0 1]
	{	mat[0][0]=1;
		mat[0][1]=0;
		mat[1][0]=0;
		mat[1][1]=1;
		return;
	}

	long long copymat[2][2];
	copymat[0][0]=mat[0][0];
	copymat[0][1]=mat[0][1];
	copymat[1][0]=mat[1][0];
	copymat[1][1]=mat[1][1];
	power(mat, n/2);// x^([n/2]).
	//now we square the result:
	//[a b]^2 =[a*a +bc, ab+ bd]
	//[c d]    [ac  +dc, bc+d*d]
	long long squaremat[2][2];
	squaremat[0][0] = (((mat[0][0]*mat[0][0])%MOD) + ((mat[0][1]*mat[1][0])%MOD))%MOD;
	squaremat[0][1] = (((mat[0][0]*mat[0][1])%MOD) + ((mat[0][1]*mat[1][1])%MOD))%MOD;
	squaremat[1][0] = (((mat[1][0]*mat[0][0])%MOD) + ((mat[1][0]*mat[1][1])%MOD))%MOD;
	squaremat[1][1] = (((mat[1][0]*mat[0][1])%MOD) + ((mat[1][1]*mat[1][1])%MOD))%MOD;

	if(n&1)	//if n is odd, we have to multiply original matrix once again.
	{	//x^n = (x^([n/2]))*(x^([n/2]))*x
		long long ans[2][2];
		ans[0][0]= (((squaremat[0][0]*copymat[0][0])%MOD) + ((squaremat[0][1]*copymat[1][0])%MOD))%MOD;
		ans[0][1]= (((squaremat[0][0]*copymat[0][1])%MOD) + ((squaremat[0][1]*copymat[1][1])%MOD))%MOD;
		ans[1][0]= (((squaremat[1][0]*copymat[0][0])%MOD) + ((squaremat[1][1]*copymat[1][0])%MOD))%MOD;
		ans[1][1]= (((squaremat[1][0]*copymat[0][1])%MOD) + ((squaremat[1][1]*copymat[1][1])%MOD))%MOD;

		mat[0][0]= ans[0][0];
		mat[0][1]= ans[0][1];
		mat[1][0]= ans[1][0];
		mat[1][1]= ans[1][1];
		return;
	}
	//if n is even, x^n = x^(n/2) * x^(n/2).
	mat[0][0]= squaremat[0][0];
	mat[0][1]= squaremat[0][1];
	mat[1][0]= squaremat[1][0];
	mat[1][1]= squaremat[1][1];
}

long long fib(long long n)
{
    long long mat[2][2] = {{1, 1}, {1, 0}};
	power(mat, n);
	return mat[0][1];
}

int main()
{	long long n;
	F[0]=F[1]=1;
	while (cin >> n)
		cout << (n==0 ? 0 : f(n-1)) << endl;
	return 0;
}
