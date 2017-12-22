// This implements sieve of Eratosthenes algorithm to find primes among numbers
// upto "LIMIT", which should not exceed "PRIMES".
// Time-complexity: O(N)
#include <iostream>
#include <algorithm>
#include <vector>

const int LIMIT  = 100000;  //size of integers array
//const int PRIMES = 10000;   //size of primes array

//linear time sieve.
std::vector <int> prime;
bool is_composite[LIMIT];

void sieve (int n) {
	std::fill (is_composite, is_composite + n, false);
	for (int i = 2; i < n; ++i) {
		if (!is_composite[i]) prime.push_back (i);
		for (int j = 0; j < prime.size () && i * prime[j] < n; ++j) {
			is_composite[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
}

using namespace std;

int main()
{
    sieve(LIMIT);
    //The following is the testing component for sieve.
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int t;
    cin>>t;
    while(t--)
    {
        int a;
        cin>>a;
        //if(binary_search(primes, primes+ PRIMES, a))
        if(!is_composite[a])
            cout << a<<" is a prime\n";
    }
    return 0;
}
