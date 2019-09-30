/** This implements Rabin Miller primality test, but the deterministic varient.
 * This uses modular exponention.
 * Note1: source : https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test
 * Since, the test is to be used only for numbers upto 2147483647, it's sufficient to test it
 * for a= 2, 3, 5, 7.
 * Time complexity : O((log N)^4)
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long ex(long long a, long long k, const long long MOD)
{
    if(k==0)    return 1;
    if(k==1)    return a%MOD;
    if(k%2)     {long long x=ex(a, (k-1)/2, MOD)%MOD; x= (x*x)%MOD; return (a*x)%MOD;}
    else        {long long y=ex(a, k/2, MOD)%MOD;     y= (y*y)%MOD; return y;}
}

bool prime(int x)				//returns true if x is a prime, false otherwise.
{	if(x==2)					//2 is a prime.
		return true;
	if(x<=1 || !(x&1))			//if x <=1 or x is even, it can't be a prime.
		return false;
	int temp = x-1, s=0, d=1;	//x-1 = (2^s)*d
	while(!(temp & 1))			//While temp is even. i.e. divisible by 2,
	{	temp>>=1;				//Keep dividing it by 2, and
		++s;					//keep counting the powers of two, and storing into 's'.
	}
	d= temp;					//x-1 = (2^s)*d.
	
	vector<int> a_val = {2, 3, 5, 7};//see note 1.
	for(int a: a_val)
	{	if(a> x-1)				//a can't be >= x.
			break;
			
		bool composite = true;	//We'll test if x is composite.
		long long temp = ex(a, d, x);	// temp = (a^d)%x.
		if(temp==1)				//This means this 'a' fails to make x composite.
			continue;
		
		for(int r=0; r<s; ++r)	//r belongs to [0, s-1].
		{	if(temp == x-1)		//temp = a^(d* (2^r)) % x.	//check the wikipedia page.
			{	composite= 0;	//if temp= -1 (mod x), this 'a' fails.
				break;
			}
			temp= (temp*temp)%x;//to increment power of two, in temp.
			//temp becomes a^(d* (2^(r+1))%x.
		}
		if(composite)			//if this 'a' classifies x as a composite.
		{	//cout << a;
			return false;
		}
	}
	return true;
}

void test()
{
	vector<int> list = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997};
	//hard-coded list of primes upto 1000.
	for(int x=0; x<1000; x++)
	{	//i.e. it classifies primes as primes, and composities as composites.
		if(prime(x) != (find(list.begin(), list.end(), x)!= list.end()))
			cout << x <<endl;
	}
}

int main()
{
	//test();	//call this to test the primality function.
	int x;
	cin>>x;
	if(prime(x))
		cout << x<<" is a prime";
	else
		cout << x<<" is composite.";
}