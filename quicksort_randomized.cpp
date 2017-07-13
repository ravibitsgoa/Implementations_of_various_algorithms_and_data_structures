#include<iostream>
#include<cstdlib>
#include<ctime>
#include<algorithm>
using namespace std;
int N;
const int NMAX=10000;
int x[NMAX];


template <typename T>
void quicksort(T *pbegin, T *pend)
{ int len=pend - pbegin;
  if(len>1)
  {                                         //choosing pivot:
    int pivot_pos=rand()%len;
    T pivot=*(pbegin + pivot_pos);          //pivot_pos'th element is chosen.
    int i=1;
    swap(*(pbegin + pivot_pos), *pbegin);   //Swapping the pivot to the 1st position.
    //cout<<pivot<<endl;
                                            //partitioning:
    for(int j=1; j<len && i<len; j++)
    { if(*(pbegin + j) <= pivot)            //Moving all elements less than the pivot to the left part.
      { swap(*(pbegin +j), *(pbegin +i));
        i++;
      }
    }
    swap(*pbegin, *(pbegin + i-1));         //moving the pivot to its correct position.
    quicksort(pbegin, pbegin + i-1);        //Only elements less than pivot need to be sorted.
    quicksort(pbegin+i, pend);              //And those bigger than pivot.
  }
  else {}                                   //base case: already sorted.
}
int main()
{ cin>>N;
  for(int i=0; i<N; i++)
    cin>>x[i];
  time_t t;
  srand((unsigned) time(&t));

  quicksort(x, x+N);
  for(int i=0; i<N; i++)
    cout<<x[i]<<' ';
  return 0;
}
