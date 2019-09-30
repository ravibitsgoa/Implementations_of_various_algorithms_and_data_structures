//This finds a^k % MOD in time O(log N).
//Whenever this runs into a problem, it asserts 0 and aborts the program, which should not happen.
#include <iostream>
#include <cassert>
const long long MOD = 1e9 + 7;

using namespace std;
long long ex(long long a, long long k)
{
    if(k==0)    return 1;
    if(k==1)    return a%MOD;
    if(k%2)     {long long x=ex(a, (k-1)/2)%MOD; assert(x>=0);   x= (x*x)%MOD; return (a*x)%MOD;}
    else        {long long y=ex(a, k/2)%MOD;     assert(y>=0);   y= (y*y)%MOD; return y;}
}

int main()
{
    //Several test-cases:
    cout<<ex(10, 1800)<<endl;
    cout<<ex(10, 18000)<<endl;
    cout<<ex(10, 180000)<<endl;
    cout<<ex(10, 1800000)<<endl;
    cout<<ex(10, 18000000)<<endl;
    cout<<ex(10, 180000000)<<endl;
    cout<<ex(10, 1800000000)<<endl;
    cout<<ex(10, 18000000000)<<endl;
    cout<<ex(10, 180000000000)<<endl;

    return 0;
}
