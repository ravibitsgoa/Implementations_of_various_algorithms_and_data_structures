// This implements sieve of Eratosthenes algorithm to find primes among numbers
// upto "LIMIT", which should not exceed "PRIMES".
// Time-complexity: O(N* lnN)
#include <cstdio>
#include <cstdlib>

const int LIMIT  = 100000;  //size of integers array
const int PRIMES = 10000;   //size of primes array

int *primes, *numbers;
int binarySearch(int n, int start, int end)
{   printf("%d",n);
    int middle = (start+end)/2;
    if (start>end)
        return -1;
    if(n==primes[middle])
        return middle;
    if (n>primes[middle] && n<=primes[middle+1])
        return middle+1;
    if (n>primes[middle])
        return binarySearch(n, middle+1, end);
    else
        return binarySearch(n, start, middle-1);
}

int main()
{   int i,j;
    //int count = 0;
    primes = (int*)malloc(sizeof(int)*PRIMES);
    numbers = (int*)malloc(sizeof(int)*LIMIT);

    //fill the array with natural numbers
    for (i=2; i<LIMIT; i++)
    {   numbers[i]=i;
    }

    //sieve the non-primes
    for (i=2; i<LIMIT; i++)
    {   if (numbers[i]!=-1)
        {   for (j=2*numbers[i]; j<LIMIT; j+=numbers[i])
                numbers[j]=-1;
        }
    }

    //transfer the primes to their own array
    j = 0;
    for (i=2; i<LIMIT && j<PRIMES; i++)
        if (numbers[i]!=-1)
            primes[j++] = numbers[i];

    //The following is the testing component for sieve.
    int t;
    scanf("%d",&t);
    while(t--)
    {   int a, b;
        scanf("%d %d",&a,&b);
        int x=binarySearch(a, 0, LIMIT);
        printf("%d\n", x);
    }
    free(primes);
    free(numbers);
    //printf("count=%dn",count);
    //count can be used to print number of primes in [a, b].
return 0;
}
