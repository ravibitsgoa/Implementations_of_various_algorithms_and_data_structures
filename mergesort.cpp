#include<iostream>
using namespace std;
//This mergesort function takes as an argument, the starting iterator and the end iterator.
//time-complexity: O(NlogN)
int inversions=0;
template <typename T>
void mergesort(T *pstart, T *pend)
{ int l=pend-pstart;
  if(l>1)
  { T* mid = pstart + l/2;
    mergesort(pstart, mid);
    mergesort(mid, pend);
    T z[l];
    int k, a=0, b=0;  //a and b are the indices of the first and second halves resp, k is overall index.
    for(k=0; k<l; k++)
    { if(*(pstart+a)< *(pstart+ ((l/2)+b)) && a<l/2)
      { z[k]=*(pstart + a); a++;
      }
      else if(b<l-(l/2))
      { z[k]=*(pstart + (l/2 + b)); b++;
        if(a<l/2) inversions+=l/2 - a;
      }
      else
      { z[k]=*(pstart + a); a++;
      }
    }
    for(k=0; k<l; k++)
    { *(pstart+k)=z[k];//copying. the linear work.
    }
  }
  else {}//base case: already sorted.
}
int main()
{ int x[10]={9,8,7,6,5,4,3,2,1,0};
  mergesort(x, x+10);
  for(int i=0; i<10; i++)
    cout<<x[i]<<' ';
  cout<<endl;
  cout<<"Number of inversions = "<<inversions;
  return 0;
}
//completed on 10th Dec 2016, 6:15 PM
