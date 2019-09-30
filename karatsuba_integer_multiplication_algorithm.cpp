//This implements Karatsuba integer multiplication algorithm that multiplies two n digit numbers in time O(n^(log3 / log2)) = O(n^1.59).
//It can handle digits of at most 10^9 digits (or max_length of std::string).
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

string sum (const string &x, const string &y);
string diff(const string &x, const string &y);
string mul (const string &x, const string &y);
string clean(const string &x);

string clean(const string &x)
{   int i;
    for(i=0; x[i]<='0' && i<x.length(); i++){}
    string cleaned(x.begin()+i, x.end());                   //Removes zeroes (if any) from most significant digit(s).
    return cleaned;
}

//This function returns difference (x-y) between two integer strings x and y.
string diff(const string &x, const string &y)
{   if(x==y)      //Obvious case.
        return "0";
    if(x[0]=='-' && y[0]!='-')
    {   string a(x.begin()+1, x.end());
        return '-'+sum(a,y);
    }
    if(y[0]=='-' && x[0]!='-')
    {   string a(y.begin()+1, y.end());
        return sum(x,a);
    }
    if(x[0]=='-' && y[0]=='-')
    {   string a(x.begin()+1, x.end());
        string b(y.begin()+1, y.end());
        return diff(y,x);
    }
    //Now, x and y both are positive.
    if(y.length()>x.length() || (y.length()==x.length() && x<y))  //If y is bigger than x.
        return '-'+diff(y, x);

    string z=x;
    int yIter=y.length()-1, zIter=z.length()-1;
    for(; yIter>=0 && zIter>=0; yIter--, zIter--)
    {   int diff=z[zIter]-y[yIter];                           //difference between current digits of the two numbers.
        if(diff<0 && zIter>0)                                 //If we need to take a carry:
        {   z[zIter-1]--;
            z[zIter]=(diff+10)+'0';
        }
        else if(diff<0 && zIter==0)                           //This happens iff original x <y, and hence, answer will be negative.
        {   //This is just not possible, because we have already handled this case.
            //If this happens, there is something really wrong going on.
            cerr<<"error, something has gone wrong. sorry.";
            assert(0);
        }
        else                                                  //If we don't need to take a carry.
        {   z[zIter]=diff+'0';
        }
    }

    for(zIter=z.length()-1; zIter>=0; zIter--)              //If z has any negative integers remaining, correct them.
    {   if(z[zIter]<'0' && zIter>0)
        {   z[zIter]+=10;
            z[zIter-1]--;
        }
    }
    return clean(z);                                        //Remove most significant zeroes.
}

//This returns sun (x+y) for two integer strings x and y.
string sum(const string &x, const string &y)
{   if(x[0]=='-' && y[0]!='-')  {string a(x.begin()+1, x.end()); return diff(y,a);}
    if(x[0]!='-' && y[0]=='-')  {string a(y.begin()+1, y.end()); return diff(x,a);}
    if(x[0]=='-' && y[0]=='-')
    {   string a(x.begin()+1, x.end());
        string b(y.begin()+1, y.end());
        return '-'+sum(a,b);
    }
    if(x=="0")
        return y;
    if(y=="0")
        return x;
    //Now, x and y both are positive.
    string s(max(x.length(), y.length())+1, '0');                            //Stores 0es in all digits of the sum.
    int xIter=x.length()-1, yIter=y.length()-1, sumIter=0;
    for(; xIter>=0 && yIter>=0; xIter--, yIter--, sumIter++)  //Stores digits of sum from the least significant to most significant.
    {   if(x[xIter]<'0' || x[xIter]>'9' )
        {   cerr<<"This is not a numeric string. error. At position "<<xIter<<" in "<<x;
            assert(0);
        }
        if(y[yIter]<'0' || y[yIter]>'9')
        {   cerr<<"This is not a numeric string. error. At position "<<yIter<<" in "<<y;
            assert(0);
        }
        int temp      = (x[xIter] -'0') + (y[yIter] -'0') + (s[sumIter] -'0');  //current digit of x + current digit of y + carry of any previous iterations.
        s[sumIter]  = (temp%10) + '0';                          //Stores current digit here.
        s[sumIter+1]= (temp/10) + '0';                          //Stores the carry here.
    }                                                         //Until at least one of the string is exhausted.

    for(; xIter>=0; xIter--, sumIter++)                       //If y is exhausted first. (i.e. y is shorter of the two.)
    {   int temp      = (x[xIter] -'0') + (s[sumIter] -'0');
        s[sumIter]  = (temp%10) + '0';
        s[sumIter+1]= (temp/10) + '0';
    }

    for(; yIter>=0; yIter--, sumIter++)                       //If x is exhausted first.
    {   int temp      = (y[yIter] -'0') + (s[sumIter] -'0');
        s[sumIter]  = (temp%10) + '0';
        s[sumIter+1]= (temp/10) + '0';
    }

    reverse(s.begin(), s.end());      //So that sum string becomes in usual order. i.e. most significant to least.
    s=clean(s);
    return s;
}

//This returns multiplication (x*y) for two strings x and y, by Karatsuba algorithm and Euclid's trick.
string mul(const string &x, const string &y)
{   int xlen=x.length(), ylen=y.length(), minlen=min(xlen, ylen);
    if(minlen==0 || x=="0" || y=="0")           //basecase 1.
        return "0";
    if(minlen==1) //If either x or y is a single digit.
    {   if(xlen==1) //If x is a single digit.
        {   string z(xlen+ylen, 0);
            int yIter=ylen-1, zIter=0, xIter=0;
            for(; yIter>=0; yIter--, zIter++)
            {   int temp    = (x[xIter] -'0') * (y[yIter] -'0') + (z[zIter] -'0')*(z[zIter]>='0');  //current digit of x * current digit of y + carry of any previous iterations.
                z[zIter]    = (temp%10) + '0';                        //Stores current digit here.
                if(temp>=10)
                    z[zIter+1]  = (temp/10) + '0';                        //Stores the carry here.
            }
            reverse(z.begin(), z.end());
            return clean(z);
        }
        else      //If y is a single digit.
        {   string z(xlen+ylen, 0);
            int yIter=0, zIter=0, xIter=xlen-1;
            for(; xIter>=0; xIter--, zIter++)
            {   int temp    = (x[xIter] -'0') * (y[yIter] -'0') + (z[zIter] -'0')*(z[zIter]>='0');  //current digit of x * current digit of y + carry of any previous iterations.
                z[zIter]    = (temp%10) + '0';                        //Stores current digit here.
                z[zIter+1]  = (temp/10) + '0';                        //Stores the carry here.
            }
            reverse(z.begin(), z.end());
            return clean(z);
        }
    }
    if(minlen%2)
        minlen++;
    string a(x.begin(), x.end()-minlen/2), b(x.end()-minlen/2, x.end());
    string c(y.begin(), y.end()-minlen/2), d(y.end()-minlen/2, y.end());

    string ac=mul(a,c), temp=mul(sum(a,b),sum(c,d)), bd=mul(b,d);
    string power((minlen/2), '0');
    string acbd=sum(ac,bd);
    temp=diff(temp,acbd);//Now, it is ad+bc.
    ac=ac+power+power;
    temp+=power;
    string multi=sum(temp, sum(ac, bd));//Order doesn't matter.
    return multi;
}

int main()
{   string a, b;
    cout<<"Enter first number.\na =\t";
    cin>>a;
    cout<<"Enter second number.\nb =\t";
    cin>>b;
    cout<<"a*b =\t"<<mul(a, b)<<'\n';
    //cout<<"a+b =\t"<<sum(a,b)<<'\n';
    return 0;
}
