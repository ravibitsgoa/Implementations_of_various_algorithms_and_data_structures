//Source: https://link.springer.com/content/pdf/10.1007/3-540-36400-5_6.pdf
//Implemented on 13th Nov 2017
#include <iostream>
using namespace std;
long long invBitwise(long long a, long long p)
{
    long long r=0, u=p, v=a, s=1;
    while(v>0)
    {   if(!(u&1))      // if u is even
        {   u>>=1;
            if(!(r&1))
            {   r>>=1;
            }
            else
            {   r= (r+p)>>1;
            }
        }
        else if(!(v&1)) //if v is even.
        {   v>>=1;
            if(!(s&1))
            {   s>>=1;
            }
            else
            {   s= (s+p)>>1;
            }
        }
        else
        {   long long x= u-v;
            if(x>0)
            {   u = x;
                r-=s;
                if(r<0)
                    r+=p;
            }
            else
            {   v = -x;
                s-=r;
                if(s<0)
                    s+=p;   
            }
        }
    }
    if(r>p)
        r-=p;
    if(r<0)
        r+=p;
    return r;
    // r is a inverse mod p.
}

long long invMontgomeryA(long long a, long long p, int &k)
{   long long r=0, u=p, v=a, s=1;
    while(v>0)
    {   ++k;   
        if(!(u&1))      // if u is even
        {   u>>=1;
            s<<=1;
        }
        else if(!(v&1)) //if v is even.
        {   v>>=1;
            r<<=1;
        }
        else
        {   long long x= u-v;
            if(x>0)
            {   u = (x>>1);
                r+=s;
                s<<=1;
            }
            else
            {   v = -(x>>1);
                s+=r;
                r<<=1;   
            }
        }
    }
    if(r>p)
        r-=p;
    return (p-r);
}   //outputs y= inverse(a) * (2**k) (mod p)

long long invMontgomeryB(long long a, long long p)
{   long long y= invMontgomeryA(a, p, 0);
    for(int i=0; i<k; i++)
    {   if(!(y&1))  //if y is even
            y>>=1;
        else
            y = (y+p)>>1;
    }
    return y;
}   //outputs y= inverse(a) (mod p)


int main()
{   long long a=1, p = 5;
    cout<< inv(1, 5);
}
